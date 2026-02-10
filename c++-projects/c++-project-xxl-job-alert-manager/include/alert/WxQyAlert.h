#pragma once

#include <string>

#include "AlertChannel.h"

// 企业微信告警
class WxQyAlert : public AlertChannel {
public:
    // 发送消息
    bool sendMsg(const std::string& title, const std::string& content) override;
};