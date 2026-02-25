#pragma once

#include <string>

#include "Logger.h"
#include "TimeHelper.h"
#include "Timestamp.h"

// 基础测试
class BaseTest {
public:
    // 获取当前时间戳
    void getTimestamp() {
        LOG_INFO("Current timestamp: %s", std::to_string(Timestamp::now().getTimestamp()).c_str());
    }

    // 当前时间戳转换为日期字符串
    void toDateString() {
        LOG_INFO("Current date: %s", Timestamp::now().toDateString().c_str());
    }

    // 当前时间戳转换为日期时间字符串
    void toDateTimeString() {
        LOG_INFO("Current date time: %s", Timestamp::now().toDateTimeString().c_str());
    }

    // 将字符串转换为时间戳（秒）
    void toUtcTimestampSec() {
        std::string datetime = "2026-02-25 17:18:20";
        LOG_INFO("Current timestamp(s): %s", std::to_string(TimeHelper::toUtcTimestampSec(datetime)).c_str());
    }

    // 将字符串转换为时间戳（毫秒）
    void toUtcTimestampMs() {
        std::string datetime = "2026-02-25 17:18:20";
        LOG_INFO("Current timestamp(ms): %s", std::to_string(TimeHelper::toUtcTimestampMs(datetime)).c_str());
    }

    // 将字符串转换为时间戳（微秒）
    void toUtcTimestampUs() {
        std::string datetime = "2026-02-25 17:18:20.123";
        LOG_INFO("Current timestamp(us): %s", std::to_string(TimeHelper::toUtcTimestampUs(datetime)).c_str());
    }
};