#include "Logger.h"

// 私有构造函数，防止外部创建对象
Logger::Logger() {
}

// 获取单例对象
Logger& Logger::instance() {
    // 静态局部变量，确保只创建一次（单例对象）
    static Logger logger;
    // 设置默认日志级别
    logger.setLogLevel(INFO);
    return logger;
}

// 设置日志级别
void Logger::setLogLevel(int logLevel) {
    this->logLevel_ = logLevel;
}

// 记录日志
void Logger::log(std::string msg) {
    switch (this->logLevel_) {
        case DEBUG:
            std::cout << "[DEBUG]";
            break;
        case INFO:
            std::cout << "[INFO]";
            break;
        case WARN:
            std::cout << "[WARN]";
            break;
        case ERROR:
            std::cout << "[ERROR]";
            break;
        case FATAL:
            std::cout << "[FATAL]";
            break;
    }
}