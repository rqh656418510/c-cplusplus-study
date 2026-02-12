#pragma once

#include "Logger.h"
#include "Timestamp.h"

// 基础测试
class BaseTest {
    // 获取当前时间
    void nowDateTime() {
        LOG_INFO("Current time: %s", Timestamp::now().toString().c_str());
    }
};