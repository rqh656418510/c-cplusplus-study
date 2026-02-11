#pragma once

#include <string>

#include "AlertLevel.h"

// 告警渠道（抽象类）
class AlertChannel {
public:
    // 虚析构函数
    virtual ~AlertChannel() = default;

    // 发送消息（纯虚函数）
    virtual bool sendMsg(const std::string& title, const std::string& content) = 0;
};