#pragma once

#include <string>
#include <thread>

#include "CurrentThread.h"
#include "LockQueue.h"
#include "NonCopyable.h"

// 定义宏
#define LOG_DEBUG(logmsgformat, ...)                        \
    do {                                                    \
        Logger& logger = Logger::getInstance();             \
        if (logger.getLogLevel() <= DEBUG) {                \
            char c[1024] = {0};                             \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
            int tid = CurrentThread::tid();                 \
            LogMessage msg = {DEBUG, c, tid};               \
            logger.log(msg);                                \
        }                                                   \
    } while (0)

#define LOG_INFO(logmsgformat, ...)                         \
    do {                                                    \
        Logger& logger = Logger::getInstance();             \
        if (logger.getLogLevel() <= INFO) {                 \
            char c[1024] = {0};                             \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
            int tid = CurrentThread::tid();                 \
            LogMessage msg = {INFO, c, tid};                \
            logger.log(msg);                                \
        }                                                   \
    } while (0)

#define LOG_WARN(logmsgformat, ...)                         \
    do {                                                    \
        Logger& logger = Logger::getInstance();             \
        if (logger.getLogLevel() <= WARN) {                 \
            char c[1024] = {0};                             \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
            int tid = CurrentThread::tid();                 \
            LogMessage msg = {WARN, c, tid};                \
            logger.log(msg);                                \
        }                                                   \
    } while (0)

#define LOG_ERROR(logmsgformat, ...)                        \
    do {                                                    \
        Logger& logger = Logger::getInstance();             \
        if (logger.getLogLevel() <= ERROR) {                \
            char c[1024] = {0};                             \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
            int tid = CurrentThread::tid();                 \
            LogMessage msg = {ERROR, c, tid};               \
            logger.log(msg);                                \
        }                                                   \
    } while (0)

#define LOG_FATAL(logmsgformat, ...)                              \
    do {                                                          \
        Logger& logger = Logger::getInstance();                   \
        if (logger.getLogLevel() <= FATAL) {                      \
            char c[1024] = {0};                                   \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__);       \
            int tid = CurrentThread::tid();                       \
            LogMessage msg = {FATAL, c, tid};                     \
            logger.log(msg);                                      \
            std::this_thread::sleep_for(std::chrono::seconds(1)); \
            exit(-1);                                             \
        }                                                         \
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
    LogLevel logLevel_;       // 日志级别
    std::string logContent_;  // 日志内容
    int threadId_;            // 打印日志的线程的 ID
};

// 日志类（单例模式）
class Logger : NonCopyable {
public:
    // 获取单例对象
    static Logger& getInstance();

    // 输出日志信息
    void log(const LogMessage& message);

    // 获取日志级别
    LogLevel getLogLevel();

    // 设置日志级别
    void setLogLevel(LogLevel level);

    // 将日志级别转换为字符串
    static std::string logLevelToString(LogLevel level);

    // 将字符串转换为日志级别
    static LogLevel stringToLogLevel(const std::string& levelStr);

private:
    // 私有构造函数
    Logger();

    // 私有析构函数
    ~Logger();

    LogLevel logLevel_;             // 记录日志级别
    std::thread writeThread_;       // 日志写入线程
    LockQueue<LogMessage> lckQue_;  // 日志缓冲队列
};