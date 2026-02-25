#include "Timestamp.h"

#include <chrono>
#include <ctime>

// 默认构造函数，初始化为 0 微秒
Timestamp::Timestamp() : microSecondsSinceEpoch_(0) {
}

// 构造函数，使用微秒数进行初始化
Timestamp::Timestamp(int64_t microSecondsSinceEpochArg) : microSecondsSinceEpoch_(microSecondsSinceEpochArg) {
}

// 获取时间戳（单位：微秒）
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

// 将字符串（格式为 YYYY-MM-DD HH:MM:SS）转换为UTC时间戳（单位：秒）
int64_t Timestamp::toUtcTimestampSec(const std::string& datetime) {
    // 字符串长度必须固定为 19，比如：2025-11-16 17:45:30
    if (datetime.size() != 19) {
        return static_cast<int64_t>(-1);
    }

    struct tm tm_time {};
    tm_time.tm_isdst = 0;  // UTC 不使用夏令时

    // 解析字符串
    const char* end = strptime(datetime.c_str(), "%Y-%m-%d %H:%M:%S", &tm_time);

    // 必须完全匹配（不能有多余字符）
    if (end == nullptr || *end != '\0') {
        return static_cast<int64_t>(-1);
    }

    // 转换为 UTC 秒
    time_t seconds = timegm(&tm_time);
    if (seconds == static_cast<time_t>(-1)) {
        return static_cast<int64_t>(-1);
    }

    return static_cast<int64_t>(seconds);
}

// 将字符串（格式为 YYYY-MM-DD HH:MM:SS）转换为UTC时间戳（单位：毫秒）
int64_t Timestamp::toUtcTimestampMs(const std::string& datetime) {
    // 字符串长度必须固定为 19，比如：2025-11-16 17:45:30
    if (datetime.size() != 19) {
        return static_cast<int64_t>(-1);
    }

    struct tm tm_time {};
    tm_time.tm_isdst = 0;  // UTC 不使用夏令时

    // 解析字符串
    const char* end = strptime(datetime.c_str(), "%Y-%m-%d %H:%M:%S", &tm_time);

    // 必须完全匹配（不能有多余字符）
    if (end == nullptr || *end != '\0') {
        return static_cast<int64_t>(-1);
    }

    // 转换为 UTC 秒
    time_t seconds = timegm(&tm_time);
    if (seconds == static_cast<time_t>(-1)) {
        return static_cast<int64_t>(-1);
    }

    // 转为毫秒
    return static_cast<int64_t>(seconds) * 1000LL;
}

// 将字符串（格式为 YYYY-MM-DD HH:MM:SS.mmm）转换为UTC时间戳（单位：微秒）
int64_t Timestamp::toUtcTimestampUs(const std::string& datetime) {
    // 字符串长度必须固定为 23，比如：2025-11-16 17:45:30.123
    if (datetime.size() != 23) {
        return static_cast<int64_t>(-1);
    }

    struct tm tm_time {};
    tm_time.tm_isdst = 0;  // UTC 不使用夏令时

    // 先解析到秒
    const char* pos = strptime(datetime.c_str(), "%Y-%m-%d %H:%M:%S", &tm_time);
    if (pos == nullptr || *pos != '.') {
        return static_cast<int64_t>(-1);
    }

    // 解析毫秒
    const char* ms_str = pos + 1;

    // 毫秒必须是 3 位数字
    if (!isdigit(ms_str[0]) || !isdigit(ms_str[1]) || !isdigit(ms_str[2]) || ms_str[3] != '\0') {
        return static_cast<int64_t>(-1);
    }

    int mill_seconds = (ms_str[0] - '0') * 100 + (ms_str[1] - '0') * 10 + (ms_str[2] - '0');

    // 转换为 UTC 秒
    time_t seconds = timegm(&tm_time);
    if (seconds == static_cast<time_t>(-1)) {
        return static_cast<int64_t>(-1);
    }

    // 转换为微秒
    int64_t us = static_cast<int64_t>(seconds) * 1000000LL + static_cast<int64_t>(mill_seconds) * 1000LL;

    return us;
}