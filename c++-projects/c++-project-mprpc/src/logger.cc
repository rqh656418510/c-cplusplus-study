#include "logger.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <thread>

// 构造函数
Logger::Logger() {
    // 设置默认的日志级别
    this->m_loglevel = INFO;

    // 启动专门写日志文件的线程
    m_writeThread = std::thread([this]() {
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

            // 检查退出标志
            if (m_lckQue.isExit()) {
                // 关闭日志文件
                fclose(pf);
                // 跳出外层 For 循环，结束日志写入线程的运行（会丢失未被写入的日志信息）
                break;
            }

            // 获取打印日志信息的线程的 ID（可能为负数）
            std::thread::id real_thread_id = message.m_threadid;
            std::ostringstream oss;
            oss << real_thread_id;
            std::string log_thread_id = oss.str();

            // 获取日志内容和日志级别的名称
            std::string& log_content = message.m_logcontent;
            std::string log_level_name = LogLevelToString(message.m_loglevel);

            // 获取当前时间
            char time_buf[128] = {0};
            sprintf(time_buf, "%d-%d-%d %d:%d:%d => %d [%s] ", now_tm->tm_year + 1900, now_tm->tm_mon + 1,
                    now_tm->tm_mday, now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec, log_thread_id.c_str(),
                    log_level_name.c_str());

            // 添加当前时间到日志内容的最前面
            log_content.insert(0, time_buf);

            // 添加换行符到日志内容的最后面
            log_content.append("\n");

            // 打印日志内容到控制台
            std::cout << log_content;

            // 将日志内容写入日志文件
            fputs(log_content.c_str(), pf);

            // 关闭日志文件
            fclose(pf);
        }
    });
}

// 析构函数
Logger::~Logger() {
    // 关闭队列，通知日志写入线程停止运行，避免发生线程死锁
    this->m_lckQue.Stop();
    // 等待日志线程安全退出
    if (m_writeThread.joinable()) {
        m_writeThread.join();
    }
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