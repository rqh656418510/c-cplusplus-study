#include "Logger.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <sstream>
#include <thread>

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

// 定义默认日志级别
static LogLevel DEFAULT_LOG_LEVEL = INFO;

// clang-format on

// 构造函数
Logger::Logger() {
    // 设置默认的日志级别
    this->logLevel_ = DEFAULT_LOG_LEVEL;

    // 启动专门写日志文件的线程
    writeThread_ = std::thread([this]() {
        for (;;) {
            // 获取当前日期
            time_t now = time(nullptr);
            tm* now_tm = localtime(&now);

            // 获取日志文件的名称
            char file_name[128];
            snprintf(file_name, sizeof(file_name), "%04d-%02d-%02d.log", now_tm->tm_year + 1900, now_tm->tm_mon + 1,
                     now_tm->tm_mday);

            // 打开日志文件
            FILE* pf = fopen(file_name, "a+");
            if (pf == nullptr) {
                std::cout << "logger file " << file_name << " open failed!" << std::endl;
                // 退出程序
                exit(EXIT_FAILURE);
            }

            // 从日志缓冲队列获取日志信息（会阻塞当前线程，直到日志队列不为空）
            LogMessage message = lckQue_.pop();

            // 只有打印已停止且队列里不存在有效任务时，才退出循环，否则继续执行直到队列为空为止
            if (lckQue_.isExited() && message.logContent_.empty()) {
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

// 输出日志信息
void Logger::log(const LogMessage& message) {
    // 将日志信息写入缓冲队列中
    this->lckQue_.push(message);
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
        this->lckQue_.stop();

        // 等待日志线程安全退出
        if (writeThread_.joinable()) {
            writeThread_.join();
        }

        // 打印日志信息
        LOG_INFO("Logger stoped");
    } catch (const std::exception& e) {
        LOG_ERROR("Logger stop failed, exception: %s", e.what());
    } catch (...) {
        LOG_ERROR("Logger stop failed, unknown exception");
    }
}

// 设置日志级别
void Logger::setLogLevel(LogLevel level) {
    this->logLevel_ = level;
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
            return "INFO";
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