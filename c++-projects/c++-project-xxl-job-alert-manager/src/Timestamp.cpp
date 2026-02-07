#include "Timestamp.h"

#include <ctime>

// 默认构造函数，初始化为 0 微秒
Timestamp::Timestamp()
    : microSecondsSinceEpoch_(0){

      };

// 构造函数，使用微秒数进行初始化
Timestamp::Timestamp(int64_t microSecondsSinceEpochArg)
    : microSecondsSinceEpoch_(microSecondsSinceEpochArg){

      };

// 将时间戳转换为字符串（比如 2025-11-16 17:45:30）
std::string Timestamp::toString() const {
    char buf[128] = {0};
    tm* tm_time = localtime(&microSecondsSinceEpoch_);
    snprintf(buf, 128, "%4d-%02d-%02d %02d:%02d:%02d", tm_time->tm_year + 1900, tm_time->tm_mon + 1, tm_time->tm_mday,
             tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);
    return buf;
}

// 获取当前时间戳
Timestamp Timestamp::now() {
    return Timestamp(time(NULL));
}

// 将字符串（比如 2025-11-16 17:45:30）转换为UTC时间戳
time_t Timestamp::toUtcTimestamp(const std::string& datetime) {
    // 判断字符串是否为空
    if (datetime.empty()) {
        return static_cast<time_t>(-1);
    }

    struct tm tm_time {};
    tm_time.tm_isdst = 0;  // UTC 不需要夏令时

    // 字符串格式：YYYY-MM-DD HH:MM:SS
    if (strptime(datetime.c_str(), "%Y-%m-%d %H:%M:%S", &tm_time) == nullptr) {
        // 字符串解析失败
        return static_cast<time_t>(-1);
    }

    // 返回UTC时间戳
    return timegm(&tm_time);
}