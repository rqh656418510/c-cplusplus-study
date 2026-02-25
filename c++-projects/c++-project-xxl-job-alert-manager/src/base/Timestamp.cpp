#include "Timestamp.h"

#include <chrono>
#include <ctime>

// 默认构造函数，初始化为 0 微秒
Timestamp::Timestamp() : microSecondsSinceEpoch_(0) {
}

// 构造函数，使用微秒数进行初始化
Timestamp::Timestamp(int64_t microSecondsSinceEpochArg) : microSecondsSinceEpoch_(microSecondsSinceEpochArg) {
}

// 获取UTC时间戳（单位：微秒）
int64_t Timestamp::getTimestamp() const {
    return microSecondsSinceEpoch_;
}

// 将时间戳转换为字符串（格式为 YYYY-MM-DD）
std::string Timestamp::toDateString() const {
    if (microSecondsSinceEpoch_ < 0) {
        return "";
    }

    char buf[128] = {0};
    time_t seconds = microSecondsSinceEpoch_ / 1000000;
    struct tm tm_time;
    if (localtime_r(&seconds, &tm_time) == nullptr) {
        return "";
    }
    snprintf(buf, sizeof(buf), "%4d-%02d-%02d", tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday);
    return buf;
}

// 将时间戳转换为字符串（格式为 YYYY-MM-DD HH:MM:SS）
std::string Timestamp::toDateTimeString() const {
    if (microSecondsSinceEpoch_ < 0) {
        return "";
    }

    char buf[128] = {0};
    time_t seconds = microSecondsSinceEpoch_ / 1000000;
    struct tm tm_time;
    if (localtime_r(&seconds, &tm_time) == nullptr) {
        return "";
    }
    snprintf(buf, sizeof(buf), "%4d-%02d-%02d %02d:%02d:%02d", tm_time.tm_year + 1900, tm_time.tm_mon + 1,
             tm_time.tm_mday, tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    return buf;
}

// 获取当前时间戳
Timestamp Timestamp::now() {
    return Timestamp(currentTimestamp());
}

// 计算当前时间戳（单位：微秒）
int64_t Timestamp::currentTimestamp() {
    // 【特别注意】这里使用的是 system_clock，而不是 steady_clock，即使用真实系统时间，受 NTP 影响
    auto now = std::chrono::system_clock::now();
    int64_t now_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
    return now_us;
}