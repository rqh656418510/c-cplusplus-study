#pragma once

#include <string>

#include "AlertChannel.h"

// 邮件告警
class EmailAlert : public AlertChannel {
public:
    // 发送消息
    bool sendMsg(const std::string& title, const std::string& content) override {
        return true;
    }
};