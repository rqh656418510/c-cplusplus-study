#pragma once

#include <iostream>

#include "Copyable.h"

// 时间戳类（基于Unix系统时间）
class Timestamp : Copyable {
public:
    // 默认构造函数，初始化为 0 微秒
    Timestamp();

    // 构造函数，使用微秒数进行初始化
    explicit Timestamp(int64_t microSecondsSinceEpochArg);

    // 获取UTC时间戳（单位：微秒）
    int64_t getTimestamp() const;

    // 将时间戳转换为字符串（格式为 YYYY-MM-DD）
    std::string toDateString() const;

    // 将时间戳转换为字符串（格式为 YYYY-MM-DD HH:MM:SS）
    std::string toDateTimeString() const;

    // 获取当前时间戳
    static Timestamp now();

private:
    // 计算当前时间戳（单位：微秒）
    static int64_t currentTimestamp();

    // 自纪元（1970年01月01日）以来的微秒数（UTC时间戳）
    int64_t microSecondsSinceEpoch_;
};