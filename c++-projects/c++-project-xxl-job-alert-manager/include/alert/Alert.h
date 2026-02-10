#pragma once

#include <string>

#include "NonCopyable.h"
#include "XxlJobLog.h"

// 告警工具
class Alert : NonCopyable {
public:
    // 发送企业微信应用信息
    static void sendWxQyTextMsg(const int agentId, const std::string& toUser, const std::string& msg);

    // 发送企业微信应用信息
    static void sendWxQyTextMsg(const int agentId, const std::string& toUser, const XxlJobLog& log);
};