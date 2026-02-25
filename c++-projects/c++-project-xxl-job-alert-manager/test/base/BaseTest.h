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

    // 将时间字符串转换为UTC时间戳（秒）
    void toUtcTimestampSec() {
        std::string datetime = "2026-02-25 17:18:20";
        LOG_INFO("Current utc timestamp(s): %s", std::to_string(TimeHelper::toUtcTimestampSec(datetime)).c_str());
    }

    // 将时间字符串转换为UTC时间戳（毫秒）
    void toUtcTimestampMs() {
        std::string datetime = "2026-02-25 17:18:20";
        LOG_INFO("Current utc timestamp(ms): %s", std::to_string(TimeHelper::toUtcTimestampMs(datetime)).c_str());
    }

    // 将时间字符串转换为UTC时间戳（微秒）
    void toUtcTimestampUs() {
        std::string datetime = "2026-02-25 17:18:20.123";
        LOG_INFO("Current utc timestamp(us): %s", std::to_string(TimeHelper::toUtcTimestampUs(datetime)).c_str());
    }

    // 将本地时间字符串转换为本地时间戳（秒）
    void toLocalTimestampSec() {
        std::string datetime = "2026-02-25 17:18:20";
        LOG_INFO("Current local timestamp(s): %s", std::to_string(TimeHelper::toLocalTimestampSec(datetime)).c_str());
    }

    // 将本地时间字符串转换为时间戳（毫秒）
    void toLocalTimestampMs() {
        std::string datetime = "2026-02-25 17:18:20";
        LOG_INFO("Current local timestamp(ms): %s", std::to_string(TimeHelper::toLocalTimestampMs(datetime)).c_str());
    }

    // 将本地时间字符串转换为时间戳（微秒）
    void toLocalTimestampUs() {
        std::string datetime = "2026-02-25 17:18:20.123";
        LOG_INFO("Current local timestamp(us): %s", std::to_string(TimeHelper::toLocalTimestampUs(datetime)).c_str());
    }
};