#pragma once

#include <string>

#include "lockqueue.h"

enum LogLevel {
    INFO,   // 普通日志信息
    WARN,   // 警告日志信息
    ERROR,  // 错误日志信息
};

// Mprpc 框架提供的日志系统（单例对象）
class Logger {
public:
    // 获取单例对象
    static Logger& GetInstance();

    // 设置日志级别
    void SetLogLevel(LogLevel level);

    // 写入日志信息
    void Log(std::string msg);

private:
    int m_loglevel;                   // 日志级别
    LockQueue<std::string> m_lckQue;  // 日志缓冲队列

    // 构造函数
    Logger();

    // 删除拷贝构造函数
    Logger(const Logger&) = delete;

    // 删除赋值运算操作符
    Logger& operator=(const Logger&) = delete;
};