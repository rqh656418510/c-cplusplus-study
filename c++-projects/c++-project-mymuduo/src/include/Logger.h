#pragma once

#include <iostream>
#include <string>

#include "noncopyable.h"

// 定义宏
#define LOG_DEBUG(logmsgFormat, ...)                      \
    do {                                                  \
        Loggerr& logger = Logger::instance();             \
        logger.setLogLevel(DEBUG);                        \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_AGGS__); \
        logger.log(buf);                                  \
    } while (0)

#define LOG_INFO(logmsgFormat, ...)                       \
    do {                                                  \
        Loggerr& logger = Logger::instance();             \
        logger.setLogLevel(INFO);                         \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_AGGS__); \
        logger.log(buf);                                  \
    } while (0)

#define LOG_WARN(logmsgFormat, ...)                       \
    do {                                                  \
        Loggerr& logger = Logger::instance();             \
        logger.setLogLevel(WARN);                         \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_AGGS__); \
        logger.log(buf);                                  \
    } while (0)

#define LOG_ERROR(logmsgFormat, ...)                      \
    do {                                                  \
        Loggerr& logger = Logger::instance();             \
        logger.setLogLevel(ERROR);                        \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_AGGS__); \
        logger.log(buf);                                  \
    } while (0)

#ifdef MUDEBUG
#define LOG_FATAL(logmsgFormat, ...)                      \
    do {                                                  \
        Loggerr& logger = Logger::instance();             \
        logger.setLogLevel(FATAL);                        \
        char buf[1024] = {0};                             \
        snprintf(buf, 1024, logmsgFormat, ##__VA_AGGS__); \
        logger.log(buf);                                  \
    } while (0)
#else
#define LOG_FATAL(logmsgFormat, ...)
#endif

// 日志级别
enum LogLevel {
    DEBUG,  // 调试信息
    INFO,   // 普通信息
    WARN,   // 警告信息
    ERROR,  // 错误信息
    FATAL   // 致命错误信息
};

// 日志类
class Logger : noncopyable {
public:
    // 获取单例对象
    static Logger& instance();

    // 设置日志级别
    void setLogLevel(int logLevel);

    // 记录日志
    void log(std::string msg);

private:
    // 日志级别
    int logLevel_;

    // 私有构造函数，防止外部创建对象
    Logger();
};