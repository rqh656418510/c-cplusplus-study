#pragma once

#include <chrono>
#include <string>
#include <thread>

#include "LockQueue.h"
#include "noncopyable.h"

// 定义宏
#define LOG_DEBUG(logmsgformat, ...)                                \
    do {                                                            \
        Logger& logger = Logger::instance();                        \
        if (logger.getLogLevel() <= DEBUG) {                        \
            char c[1024] = {0};                                     \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__);         \
            std::thread::id thread_id = std::this_thread::get_id(); \
            LogMessage msg = {DEBUG, c, thread_id};                 \
            logger.log(msg);                                        \
        }                                                           \
    } while (0)

#define LOG_INFO(logmsgformat, ...)                                 \
    do {                                                            \
        Logger& logger = Logger::instance();                        \
        if (logger.getLogLevel() <= INFO) {                         \
            char c[1024] = {0};                                     \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__);         \
            std::thread::id thread_id = std::this_thread::get_id(); \
            LogMessage msg = {INFO, c, thread_id};                  \
            logger.log(msg);                                        \
        }                                                           \
    } while (0)

#define LOG_WARN(logmsgformat, ...)                                 \
    do {                                                            \
        Logger& logger = Logger::instance();                        \
        if (logger.getLogLevel() <= WARN) {                         \
            char c[1024] = {0};                                     \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__);         \
            std::thread::id thread_id = std::this_thread::get_id(); \
            LogMessage msg = {WARN, c, thread_id};                  \
            logger.log(msg);                                        \
        }                                                           \
    } while (0)

#define LOG_ERROR(logmsgformat, ...)                                \
    do {                                                            \
        Logger& logger = Logger::instance();                        \
        if (logger.getLogLevel() <= ERROR) {                        \
            char c[1024] = {0};                                     \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__);         \
            std::thread::id thread_id = std::this_thread::get_id(); \
            LogMessage msg = {ERROR, c, thread_id};                 \
            logger.log(msg);                                        \
        }                                                           \
    } while (0)

#define LOG_FATAL(logmsgformat, ...)                                \
    do {                                                            \
        Logger& logger = Logger::instance();                        \
        if (logger.getLogLevel() <= FATAL) {                        \
            char c[1024] = {0};                                     \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__);         \
            std::thread::id thread_id = std::this_thread::get_id(); \
            LogMessage msg = {FATAL, c, thread_id};                 \
            logger.log(msg);                                        \
            std::this_thread::sleep_for(std::chrono::seconds(1));   \
            exit(-1);                                               \
        }                                                           \
    } while (0)

// 日志级别（DEBUG < INFO < WARN < ERROR < FATAL）
enum LogLevel {
    DEBUG,  // 调试日志信息
    INFO,   // 普通日志信息
    WARN,   // 警告日志信息
    ERROR,  // 错误日志信息
    FATAL   // 致命错误信息
};

// 日志信息
struct LogMessage {
    LogLevel m_loglevel;         // 日志级别
    std::string m_logcontent;    // 日志内容
    std::thread::id m_threadid;  // 打印日志的线程的 ID
};

// 日志系统（单例对象，负责异步写入日志文件）
class Logger : noncopyable {
public:
    // 获取单例对象
    static Logger& instance();

    // 写入日志信息
    void log(const LogMessage& message);

    // 获取日志级别
    LogLevel getLogLevel();

    // 设置日志级别
    void setLogLevel(LogLevel level);

private:
    LogLevel m_loglevel;             // 记录日志级别
    std::thread m_writeThread;       // 日志写入线程
    LockQueue<LogMessage> m_lckQue;  // 日志缓冲队列

    // 构造函数
    Logger();

    // 析构函数
    ~Logger();

    // 获取日志级别的名称
    std::string LogLevelToString(LogLevel level);
};
