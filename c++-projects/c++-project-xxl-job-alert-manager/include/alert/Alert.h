#pragma once

#include <string>

#include "XxlJobLog.h"

// 告警工具
class Alert {
public:
    // 发送企业微信应用信息
    static void sendWxQyTextMsg(const int agentId, const std::string& toUser, const std::string& msg);

    // 发送企业微信应用信息
    static void sendWxQyTextMsg(const int agentId, const std::string& toUser, const XxlJobLog& log);
};