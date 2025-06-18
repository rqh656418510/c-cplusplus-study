#include "logger.h"

// 构造函数
Logger::Logger() {
    this->m_loglevel = INFO;
}

// 获取单例对象
Logger& Logger::GetInstance() {
    // 局部静态变量（线程安全）
    static Logger logger;
    return logger;
}

// 设置日志级别
void Logger::SetLogLevel(LogLevel level) {
    this->m_loglevel = level;
}

// 写入日志信息
void Logger::Log(std::string msg) {
    // 将数据写入缓冲队列中
    this->m_lckQue.Push(msg);
}
