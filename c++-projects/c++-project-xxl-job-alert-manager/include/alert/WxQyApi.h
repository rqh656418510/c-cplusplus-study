#pragma once

#include <string>

#include "WxQySendMsgReq.h"
#include "json.hpp"

// 类型重定义
using json = nlohmann::json;

// 企业微信API工具
class WxQyApi {
public:
    // 获取最新的AccessToken
    static std::string getAccessToken();

    // 发送应用消息
    static bool sendMessage(const WxQySendMsgReq& req);
};