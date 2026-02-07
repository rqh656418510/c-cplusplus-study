// clang-format off

#pragma once

// 定义宏，启用 httplib 的 HTTPS 支持，需要依赖 OpenSSL
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

// 引入 JSON 序列化库
#include "json.hpp"
using json = nlohmann::json;

#include <string>
#include "WxQySendMsgReq.h"

// 企业微信API工具
class WxQyApi {
public:
    // 获取最新的AccessToken
    static std::string getAccessToken();

    // 发送应用消息
    static void sendMessage(const WxQySendMsgReq& req);
};