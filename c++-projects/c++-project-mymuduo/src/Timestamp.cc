#include "Timestamp.h"

#include <time.h>

// 默认构造函数，初始化为 0 微秒
Timestamp::Timestamp()
    : microSecondsSinceEpoch_(0){

      };

// 构造函数，使用微秒数进行初始化
Timestamp::Timestamp(int64_t microSecondsSinceEpochArg)
    : microSecondsSinceEpoch_(microSecondsSinceEpochArg){

      };

// 将时间戳转换为字符串表示（比如 2025-11-16 17:45:30）
std::string Timestamp::toString() const {
    char buf[128] = {0};
    tm *tm_time = localtime(&microSecondsSinceEpoch_);
    snprintf(buf, 128, "%4d-%02d-%02d %02d:%02d:%02d", tm_time->tm_year + 1900, tm_time->tm_mon + 1, tm_time->tm_mday,
             tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);
    return buf;
}

// 获取当前时间戳
Timestamp Timestamp::now() {
    return Timestamp(time(NULL));
}