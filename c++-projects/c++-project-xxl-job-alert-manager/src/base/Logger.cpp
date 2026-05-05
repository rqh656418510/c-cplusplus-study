#include "Logger.h"

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <exception>
#include <iostream>
#include <sstream>
#include <thread>

#include "CurrentThread.h"
#include "Timestamp.h"

// clang-format off

// 定义宏（跨平台获取当前调用的函数名称）
#if defined(__GNUC__) || defined(__clang__)
    #define FUNC_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define FUNC_NAME __FUNCSIG__
#else
    #define FUNC_NAME __func__
#endif

// clang-format on

// 定义默认日志级别
static LogLevel DEFAULT_LOG_LEVEL = INFO;
static std::string DEFAULT_LOG_LEVEL_NAME = "INFO";

// 去掉首尾的空白字符，去掉末尾多余的 '/'，空字符串视为 "."
std::string normalizeLogFileDirectory(std::string dir) {
    auto not_space = [](unsigned char c) { return c != ' ' && c != '\t' && c != '\r' && c != '\n'; };
    while (!dir.empty() && !not_space(static_cast<unsigned char>(dir.front()))) {
        dir.erase(0, 1);
    }
    while (!dir.empty() && !not_space(static_cast<unsigned char>(dir.back()))) {
        dir.pop_back();
    }
    if (dir.empty()) {
        return ".";
    }
    while (dir.size() > 1 && dir.back() == '/') {
        dir.pop_back();
    }
    return dir;
}

// 将文件名解析为日历日期（文件名格式必须为 YYYY-MM-DD.log）
bool parseDailyLogFileName(const char* name, int* y, int* m, int* d) {
    int yy = 0;
    int mm = 0;
    int dd = 0;
    if (std::sscanf(name, "%d-%d-%d.log", &yy, &mm, &dd) != 3) {
        return false;
    }
    if (yy < 1970 || yy > 2100 || mm < 1 || mm > 12 || dd < 1 || dd > 31) {
        return false;
    }
    *y = yy;
    *m = mm;
    *d = dd;
    return true;
}

// 将年、月、日转换为本地时间（0 点 0 分 0 秒）
std::time_t localMidnightForYmd(int year, int month, int day) {
    std::tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    return std::mktime(&t);
}

// 删除 directory 目录下早于「今天 0 点 − maxRetentionDays」的 YYYY-MM-DD.log 普通文件
void removeExpiredDailyLogFiles(int maxRetentionDays, const char* directory) {
    if (maxRetentionDays <= 0 || directory == nullptr) {
        return;
    }

    std::time_t now = std::time(nullptr);
    std::tm* today_tm = std::localtime(&now);
    if (today_tm == nullptr) {
        return;
    }

    std::tm limit_tm = *today_tm;
    limit_tm.tm_hour = 0;
    limit_tm.tm_min = 0;
    limit_tm.tm_sec = 0;
    limit_tm.tm_mday -= maxRetentionDays;
    std::time_t limit_time = std::mktime(&limit_tm);
    if (limit_time == static_cast<std::time_t>(-1)) {
        return;
    }

    DIR* dir = opendir(directory);
    if (dir == nullptr) {
        return;
    }

    while (struct dirent* ent = readdir(dir)) {
        if (ent->d_name[0] == '.') {
            continue;
        }
        int y = 0;
        int m = 0;
        int d = 0;
        if (!parseDailyLogFileName(ent->d_name, &y, &m, &d)) {
            continue;
        }

        char path[512];
        std::snprintf(path, sizeof(path), "%s/%s", directory, ent->d_name);

        struct stat st;
        if (stat(path, &st) != 0 || !S_ISREG(st.st_mode)) {
            continue;
        }

        std::time_t file_day = localMidnightForYmd(y, m, d);
        if (file_day == static_cast<std::time_t>(-1)) {
            continue;
        }
        if (file_day < limit_time && unlink(path) != 0) {
            // 日志文件删除失败时不打印日志信息，避免与写日志线程互相干扰；静默忽略
        }
    }

    closedir(dir);
}

// 构造函数
Logger::Logger() {
    // 设置默认的日志级别
    this->logLevel_ = DEFAULT_LOG_LEVEL;

    // 启动专门写日志文件的线程
    writeThread_ = std::thread([this]() {
        int last_year = -1;
        int last_mon = -1;
        int last_mday = -1;

        for (;;) {
            // 获取当前时间（真实系统时间，受NTP影响）
            std::time_t now = std::time(nullptr);
            std::tm* now_tm = std::localtime(&now);
            if (now_tm == nullptr) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }

            int cy = now_tm->tm_year + 1900;
            int cm = now_tm->tm_mon + 1;
            int cd = now_tm->tm_mday;

            // 获取日志目录
            std::string log_dir;
            {
                std::lock_guard<std::mutex> lock(logFileDirMutex_);
                log_dir = logFileDirectory_;
            }

            // 删除过期的日志文件
            if (cy != last_year || cm != last_mon || cd != last_mday) {
                removeExpiredDailyLogFiles(logFileMaxRetentionDays_.load(std::memory_order_relaxed), log_dir.c_str());
                last_year = cy;
                last_mon = cm;
                last_mday = cd;
            }

            // 获取日志文件的名称
            char file_name[128];
            snprintf(file_name, sizeof(file_name), "%04d-%02d-%02d.log", now_tm->tm_year + 1900, now_tm->tm_mon + 1,
                     now_tm->tm_mday);

            // 拼接日志文件的完整路径
            char log_path[768];
            if (log_dir == ".") {
                std::snprintf(log_path, sizeof(log_path), "%s", file_name);
            } else {
                std::snprintf(log_path, sizeof(log_path), "%s/%s", log_dir.c_str(), file_name);
            }

            // 打开日志文件
            FILE* pf = fopen(log_path, "a+");
            if (pf == nullptr) {
                // 打印日志内容到控制台
                char buf[512];
                snprintf(buf, sizeof(buf), "Logger file [%s] open failed", log_path);
                log_direct(buf, LogLevel::FATAL);
                // 退出应用程序
                exit(EXIT_FAILURE);
            }

            // 从日志缓冲队列获取日志信息（会阻塞当前线程，直到日志队列不为空）
            LogMessage message = queue_.pop();

            // 只有打印已停止且队列里不存在有效任务时，才退出循环，否则继续执行直到队列为空为止
            if (queue_.isExited() && message.logContent_.empty()) {
                // 关闭日志文件
                fclose(pf);
                // 跳出外层 For 循环，结束日志写入线程的运行
                break;
            }

            // 获取打印日志信息的线程的 ID（由外部传入，是 Linux 内核线程 ID）
            int log_thread_id = message.threadId_;

            // 获取日志内容和日志级别的名称
            std::string& log_content = message.logContent_;
            std::string log_level_name = logLevelToString(message.logLevel_);

            // 获取当前时间
            char time_buf[128] = {0};

            snprintf(time_buf, sizeof(time_buf), "%4d-%02d-%02d %02d:%02d:%02d => %d [%s] ", now_tm->tm_year + 1900,
                     now_tm->tm_mon + 1, now_tm->tm_mday, now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec,
                     log_thread_id, log_level_name.c_str());

            // 拼接最终的日志内容
            std::ostringstream oss;
            oss << time_buf << log_content << "\n";
            std::string final_log_content = oss.str();

            // 打印日志内容到控制台
            std::cout << final_log_content;

            // 将日志内容写入日志文件
            fputs(final_log_content.c_str(), pf);

            // 关闭日志文件
            fclose(pf);
        }
    });
}

// 析构函数
Logger::~Logger() {
    // 停止记录日志
    if (!this->stoped_) {
        this->stop();
    }
}

// 获取单例对象
Logger& Logger::getInstance() {
    // 静态局部变量（线程安全）
    static Logger logger;
    return logger;
}

// 输出日志信息（记录日志文件）
void Logger::log(const LogMessage& message) {
    // 将日志信息写入缓冲队列中
    this->queue_.push(message);
}

// 输出日志信息（不记录日志文件）
void Logger::log_direct(const char* message, LogLevel level) {
    char time_buf[32];
    char log_buf[1024];

    // 获取当前时间（真实系统时间，受NTP影响）
    std::time_t now = std::time(nullptr);
    std::tm* tm_now = std::localtime(&now);

    // 格式化时间
    snprintf(time_buf, sizeof(time_buf), "%04d-%02d-%02d %02d:%02d:%02d", tm_now->tm_year + 1900, tm_now->tm_mon + 1,
             tm_now->tm_mday, tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);

    // 拼接完整日志
    snprintf(log_buf, sizeof(log_buf), "%s => %d [%s] %s", time_buf, CurrentThread::tid(),
             logLevelToString(level).c_str(), message);

    // 输出日志信息
    std::puts(log_buf);
}

// 停止记录日志
void Logger::stop() {
    try {
        // 判断是否已停止记录日志
        if (this->stoped_) {
            return;
        }

        // 更新停止标识
        this->stoped_ = true;

        // 关闭队列，通知日志写入线程停止运行，避免发生线程死锁
        this->queue_.stop();

        // 等待日志线程安全退出
        if (writeThread_.joinable()) {
            writeThread_.join();
        }

        // 打印日志信息
        log_direct("Logger stopped", LogLevel::INFO);
    } catch (const std::exception& e) {
        char buf[512];
        snprintf(buf, sizeof(buf), "Logger stop failed, exception: %s", e.what());
        log_direct(buf, LogLevel::ERROR);
    } catch (...) {
        log_direct("Logger stop failed, unknown exception", LogLevel::ERROR);
    }
}

// 设置日志级别
void Logger::setLogLevel(LogLevel level) {
    this->logLevel_ = level;
}

// 设置日志文件最大保留天数
void Logger::setLogFileMaxRetentionDays(int days) {
    if (days < 0) {
        days = 0;
    }
    logFileMaxRetentionDays_.store(days, std::memory_order_relaxed);
}

// 设置日志目录
void Logger::setLogFileDirectory(const std::string& directory) {
    std::string normalized = normalizeLogFileDirectory(directory);
    std::lock_guard<std::mutex> lock(logFileDirMutex_);
    logFileDirectory_ = normalized;
}

// 获取日志级别
LogLevel Logger::getLogLevel() {
    return this->logLevel_;
}

// 将日志级别转换为字符串
std::string Logger::logLevelToString(LogLevel level) {
    switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARN:
            return "WARN";
        case ERROR:
            return "ERROR";
        case FATAL:
            return "FATAL";
        default:
            return DEFAULT_LOG_LEVEL_NAME;
    }
}

// 将字符串转换为日志级别
LogLevel Logger::stringToLogLevel(const std::string& levelStr) {
    // 转换为大写
    std::string upperStr = levelStr;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), [](unsigned char c) { return std::toupper(c); });

    // 返回对应的日志级别
    if (upperStr == "DEBUG") return DEBUG;
    if (upperStr == "INFO") return INFO;
    if (upperStr == "WARN") return WARN;
    if (upperStr == "ERROR") return ERROR;
    if (upperStr == "FATAL") return FATAL;

    // 返回默认日志级别
    return DEFAULT_LOG_LEVEL;
}