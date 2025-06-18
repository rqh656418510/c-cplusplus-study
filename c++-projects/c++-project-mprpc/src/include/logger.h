#pragma once

#include <string>

#include "lockqueue.h"

// 定义宏
#define LOG_INFO(logmsgformat, ...)                         \
    do {                                                    \
        Logger& logger = Logger::GetInstance();             \
        if (logger.GetLogLevel() <= INFO) {                 \
            char c[1024] = {0};                             \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
            LogMessage msg = {c, INFO};                     \
            logger.Log(msg);                                \
        }                                                   \
    } while (0)

#define LOG_WARN(logmsgformat, ...)                         \
    do {                                                    \
        Logger& logger = Logger::GetInstance();             \
        if (logger.GetLogLevel() <= WARN) {                 \
            char c[1024] = {0};                             \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
            LogMessage msg = {c, WARN};                     \
            logger.Log(msg);                                \
        }                                                   \
    } while (0)

#define LOG_ERROR(logmsgformat, ...)                        \
    do {                                                    \
        Logger& logger = Logger::GetInstance();             \
        if (logger.GetLogLevel() <= ERROR) {                \
            char c[1024] = {0};                             \
            snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
            LogMessage msg = {c, ERROR};                    \
            logger.Log(msg);                                \
        }                                                   \
    } while (0)

// 日志级别（INFO < WARN < ERROR）
enum LogLevel {
    INFO,   // 普通日志信息
    WARN,   // 警告日志信息
    ERROR,  // 错误日志信息
};

// 日志信息
struct LogMessage {
    std::string m_content;  // 日志内容
    LogLevel m_loglevel;    // 日志级别
};

// Mprpc 框架提供的日志系统（单例对象，异步写入日志文件）
class Logger {
public:
    // 获取单例对象
    static Logger& GetInstance();

    // 写入日志信息
    void Log(LogMessage message);

    // 获取日志级别
    LogLevel GetLogLevel();

    // 设置日志级别
    void SetLogLevel(LogLevel level);

private:
    LogLevel m_loglevel;             // 记录日志级别
    LockQueue<LogMessage> m_lckQue;  // 日志缓冲队列

    // 构造函数
    Logger();

    // 删除拷贝构造函数
    Logger(const Logger&) = delete;

    // 删除赋值运算操作符
    Logger& operator=(const Logger&) = delete;

    // 获取日志级别的名称
    std::string LogLevelToString(LogLevel level);
};