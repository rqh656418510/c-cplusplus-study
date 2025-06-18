#include "logger.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

// 构造函数
Logger::Logger() {
    // 设置默认的日志级别
    this->m_loglevel = INFO;

    // 启动专门写日志文件的线程
    std::thread writeTask([this]() {
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
                exit(EXIT_FAILURE);
            }

            // 从日志缓冲队列获取日志信息（会阻塞当前线程，直到日志队列不为空）
            LogMessage message = m_lckQue.Pop();
            std::string& log_content = message.m_content;
            std::string log_level = LogLevelToString(message.m_loglevel);

            // 获取当前时间
            char time_buf[128] = {0};
            sprintf(time_buf, "%d-%d-%d %d:%d:%d => [%s] ", now_tm->tm_year + 1900, now_tm->tm_mon + 1, now_tm->tm_mday,
                    now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec, log_level.c_str());

            // 添加当前时间到日志信息的最前面
            log_content.insert(0, time_buf);

            // 添加换行符到日志信息的最后面
            log_content.append("\n");

            // 打印日志信息到控制台
            std::cout << log_content;

            // 将日志信息写入日志文件
            fputs(log_content.c_str(), pf);

            // 关闭日志文件
            fclose(pf);
        }
    });

    // 设置分离线程
    writeTask.detach();
}

// 获取单例对象
Logger& Logger::GetInstance() {
    // 局部静态变量（线程安全）
    static Logger logger;
    return logger;
}

// 写入日志信息
void Logger::Log(LogMessage message) {
    // 将日志信息写入缓冲队列中
    this->m_lckQue.Push(message);
}

// 设置日志级别
void Logger::SetLogLevel(LogLevel level) {
    this->m_loglevel = level;
}

// 获取日志级别
LogLevel Logger::GetLogLevel() {
    return this->m_loglevel;
}

// 获取日志级别的名称
std::string Logger::LogLevelToString(LogLevel level) {
    switch (level) {
        case INFO:
            return "INFO";
        case WARN:
            return "WARN";
        case ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}