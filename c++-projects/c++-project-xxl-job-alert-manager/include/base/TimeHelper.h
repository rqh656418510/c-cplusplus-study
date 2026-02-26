#pragma once

#include <string>

#include "NonCopyable.h"

// 时间处理工具（单例模式）
class TimeHelper : NonCopyable {
public:
    // 获取单例对象
    static TimeHelper& getInstance();

    // 将UTC时间字符串（格式为 YYYY-MM-DD HH:MM:SS）转换为UTC时间戳（单位：秒）
    int64_t toUtcTimestampSec(const std::string& datetime);

    // 将UTC时间字符串（格式为 YYYY-MM-DD HH:MM:SS）转换为UTC时间戳（单位：毫秒）
    int64_t toUtcTimestampMs(const std::string& datetime);

    // 将UTC时间字符串（格式为 YYYY-MM-DD HH:MM:SS.mmm）转换为UTC时间戳（单位：微秒）
    int64_t toUtcTimestampUs(const std::string& datetime);

    // 将本地时间字符串（格式为 YYYY-MM-DD HH:MM:SS）转换为UTC时间戳（单位：秒）
    int64_t localToUtcTimestampSec(const std::string& datetime);

    // 将本地时间字符串（格式为 YYYY-MM-DD HH:MM:SS）转换为UTC时间戳（单位：毫秒）
    int64_t localToUtcTimestampMs(const std::string& datetime);

    // 将本地时间字符串（格式为 YYYY-MM-DD HH:MM:SS.mmm）转换为UTC时间戳（单位：微秒）
    int64_t localToUtcTimestampUs(const std::string& datetime);

private:
    // 私有构造函数
    TimeHelper() = default;

    // 私有析构函数
    ~TimeHelper() = default;
};