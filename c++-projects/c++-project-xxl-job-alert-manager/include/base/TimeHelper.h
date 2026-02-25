#pragma once

#include <string>

// 时间工具
class TimeHelper {
public:
    // 将时间字符串（格式为 YYYY-MM-DD HH:MM:SS）转换为UTC时间戳（单位：秒）
    static int64_t toUtcTimestampSec(const std::string& datetime);

    // 将时间字符串（格式为 YYYY-MM-DD HH:MM:SS）转换为UTC时间戳（单位：毫秒）
    static int64_t toUtcTimestampMs(const std::string& datetime);

    // 将时间字符串（格式为 YYYY-MM-DD HH:MM:SS.mmm）转换为UTC时间戳（单位：微秒）
    static int64_t toUtcTimestampUs(const std::string& datetime);
};
