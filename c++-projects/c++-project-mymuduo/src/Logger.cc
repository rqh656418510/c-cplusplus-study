#include "Logger.h"

#include <sstream>

#include "Timestamp.h"

// clang-format off

// 定义宏（设置 Debug 模式）
#ifdef MYMUDUO_DEBUG
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
}

// 析构函数
Logger::~Logger() {
}

// 获取单例对象
Logger& Logger::instance() {
    // 局部静态变量（线程安全）
    static Logger logger;
    return logger;
}

// 输出日志信息
void Logger::log(const LogMessage& message) {
    // 首先在外面构建好完整的字符串（避免多次 << 竞争）
    std::ostringstream oss;
    oss << Timestamp::now().toString() << " => " << message.threadId_ << " [" << logLevelToString(message.logLevel_)
        << "] " << message.logContent_ << '\n';

    std::string s = oss.str();

    // 然后一次性写入，不使用 std::endl（避免隐式 flush）
    std::fwrite(s.data(), 1, s.size(), stdout);
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
