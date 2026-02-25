#pragma once

#include <iostream>

#include "Copyable.h"

// 时间戳类
class Timestamp : Copyable {
public:
    // 默认构造函数，初始化为 0 微秒
    Timestamp();

    // 构造函数，使用微秒数进行初始化
    explicit Timestamp(int64_t microSecondsSinceEpochArg);

    // 获取时间戳（单位：微妙）
    int64_t getTimestamp() const;

    // 将时间戳转换为字符串（比如 2025-11-16）
    std::string toDateString() const;

    // 将时间戳转换为字符串（比如 2025-11-16 17:45:30）
    std::string toDateTimeString() const;

    // 获取当前时间戳
    static Timestamp now();

    // 将字符串（比如 2025-11-16 17:45:30）转换为UTC时间戳
    static time_t toUtcTimestamp(const std::string& datetime);

private:
    // 计算当前时间戳（单位：微妙）
    static int64_t currentTimestamp();

    int64_t microSecondsSinceEpoch_;  // 自纪元（1970年1月1日）以来的微秒数
};