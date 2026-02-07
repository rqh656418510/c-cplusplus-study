#include "Logger.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <thread>

#include "Timestamp.h"

// clang-format off

// 定义宏（设置 Debug 模式）
#ifdef ALERT_DEBUG
    constexpr bool kIsDebugMode = true;
#else
    constexpr bool kIsDebugMode = false;
#endif

// 定义宏（跨平台获取当前调用的函数名称）
#if defined(__GNUC__) || defined(__clang__)
    #define FUNC_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define FUNC_NAME __FUNCSIG__
#else
    #define FUNC_NAME __func__
#endif

// clang-format on

// 构造函数
Logger::Logger() {
    // 设置默认的日志级别
    this->logLevel_ = !kIsDebugMode ? INFO : DEBUG;

    // 启动专门写日志文件的线程
    writeThread_ = std::thread([this]() {
        for (;;) {
            // 获取当前日期
            time_t now = time(nullptr);
            tm* now_tm = localtime(&now);

            // 获取日志文件的名称
            char file_name[128];
            sprintf(file_name, "%d-%d-%d-log.txt", now_tm->tm_year + 1900, now_tm->tm_mon + 1, now_tm->tm_mday);

            // 打开日志文件
            FILE* pf = fopen(file_name, "a+");
            if (pf == nullptr) {
                std::cout << "logger file " << file_name << " open failed!" << std::endl;
                // 退出程序
                exit(EXIT_FAILURE);
            }

            // 从日志缓冲队列获取日志信息（会阻塞当前线程，直到日志队列不为空）
            LogMessage message = lckQue_.Pop();

            // 检查退出标志
            if (lckQue_.isExit()) {
                // 关闭日志文件
                fclose(pf);
                // 跳出外层 For 循环，结束日志写入线程的运行（会丢失未被写入的日志信息）
                break;
            }

            // 获取打印日志信息的线程的 ID（由外部传入，是 Linux 内核线程 ID）
            int log_thread_id = message.threadId_;

            // 获取日志内容和日志级别的名称
            std::string& log_content = message.logContent_;
            std::string log_level_name = logLevelToString(message.logLevel_);

            // 获取当前时间
            char time_buf[128] = {0};
            sprintf(time_buf, "%d-%d-%d %d:%d:%d => %d [%s] ", now_tm->tm_year + 1900, now_tm->tm_mon + 1,
                    now_tm->tm_mday, now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec, log_thread_id,
                    log_level_name.c_str());

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
    // 关闭队列，通知日志写入线程停止运行，避免发生线程死锁
    this->lckQue_.Stop();
    // 等待日志线程安全退出
    if (writeThread_.joinable()) {
        writeThread_.join();
    }
}

// 获取单例对象
Logger& Logger::instance() {
    // 静态局部变量（线程安全）
    static Logger logger;
    return logger;
}

// 输出日志信息
void Logger::log(const LogMessage& message) {
    // 将日志信息写入缓冲队列中
    this->lckQue_.Push(message);
}

// 设置日志级别
void Logger::setLogLevel(LogLevel level) {
    this->logLevel_ = level;
}

// 获取日志级别
LogLevel Logger::getLogLevel() {
    return this->logLevel_;
}

// 获取日志级别的名称
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
            return "UNKNOWN";
    }
}
