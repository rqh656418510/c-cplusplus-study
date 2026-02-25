#include "TimeHelper.h"

#include <chrono>
#include <ctime>

// 将时间字符串（格式为 YYYY-MM-DD HH:MM:SS）转换为UTC时间戳（单位：秒）
int64_t TimeHelper::toUtcTimestampSec(const std::string& datetime) {
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

// 将时间字符串（格式为 YYYY-MM-DD HH:MM:SS）转换为UTC时间戳（单位：毫秒）
int64_t TimeHelper::toUtcTimestampMs(const std::string& datetime) {
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

// 将时间字符串（格式为 YYYY-MM-DD HH:MM:SS.mmm）转换为UTC时间戳（单位：微秒）
int64_t TimeHelper::toUtcTimestampUs(const std::string& datetime) {
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

    int milli_seconds = (ms_str[0] - '0') * 100 + (ms_str[1] - '0') * 10 + (ms_str[2] - '0');

    // 转换为 UTC 秒
    time_t seconds = timegm(&tm_time);
    if (seconds == static_cast<time_t>(-1)) {
        return static_cast<int64_t>(-1);
    }

    // 转换为微秒
    int64_t us = static_cast<int64_t>(seconds) * 1000000LL + static_cast<int64_t>(milli_seconds) * 1000LL;

    return us;
}

// 将本地时间字符串（格式为 YYYY-MM-DD HH:MM:SS）转换为UTC时间戳（单位：秒）
int64_t TimeHelper::toLocalTimestampSec(const std::string& datetime) {
    // 字符串长度必须固定为 19，比如：2025-11-16 17:45:30
    if (datetime.size() != 19) {
        return static_cast<int64_t>(-1);
    }

    struct tm tm_time {};
    tm_time.tm_isdst = -1;  // 自动判断是否为夏令时

    // 解析字符串
    const char* end = strptime(datetime.c_str(), "%Y-%m-%d %H:%M:%S", &tm_time);

    // 必须完全匹配（不能有多余字符）
    if (end == nullptr || *end != '\0') {
        return static_cast<int64_t>(-1);
    }

    // 使用 mktime() 将本地时间转换为 UTC 秒
    time_t seconds = mktime(&tm_time);
    if (seconds == static_cast<time_t>(-1)) {
        return static_cast<int64_t>(-1);
    }

    return static_cast<int64_t>(seconds);
}

// 将本地时间字符串（格式为 YYYY-MM-DD HH:MM:SS）转换为本地时间戳（单位：毫秒）
int64_t TimeHelper::toLocalTimestampMs(const std::string& datetime) {
    // 字符串长度必须固定为 19，比如：2025-11-16 17:45:30
    if (datetime.size() != 19) {
        return static_cast<int64_t>(-1);
    }

    struct tm tm_time {};
    tm_time.tm_isdst = -1;  // 自动判断是否为夏令时

    // 解析字符串
    const char* end = strptime(datetime.c_str(), "%Y-%m-%d %H:%M:%S", &tm_time);

    // 必须完全匹配（不能有多余字符）
    if (end == nullptr || *end != '\0') {
        return static_cast<int64_t>(-1);
    }

    // 使用 mktime() 将本地时间转换为 UTC 秒
    time_t seconds = mktime(&tm_time);
    if (seconds == static_cast<time_t>(-1)) {
        return static_cast<int64_t>(-1);
    }

    // 转为毫秒
    return static_cast<int64_t>(seconds) * 1000LL;
}

// 将本地时间字符串（格式为 YYYY-MM-DD HH:MM:SS.mmm）转换为本地时间戳（单位：微秒）
int64_t TimeHelper::toLocalTimestampUs(const std::string& datetime) {
    // 字符串长度必须固定为 23，比如：2025-11-16 17:45:30.123
    if (datetime.size() != 23) {
        return static_cast<int64_t>(-1);
    }

    struct tm tm_time {};
    tm_time.tm_isdst = -1;  // 自动判断是否为夏令时

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

    int milli_seconds = (ms_str[0] - '0') * 100 + (ms_str[1] - '0') * 10 + (ms_str[2] - '0');

    // 使用 mktime() 将本地时间转换为秒
    time_t seconds = mktime(&tm_time);
    if (seconds == static_cast<time_t>(-1)) {
        return static_cast<int64_t>(-1);
    }

    // 转换为微秒
    int64_t us = static_cast<int64_t>(seconds) * 1000000LL + static_cast<int64_t>(milli_seconds) * 1000LL;

    return us;
}