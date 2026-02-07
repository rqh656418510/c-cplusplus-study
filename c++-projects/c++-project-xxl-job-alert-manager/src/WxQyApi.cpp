#include "WxQyApi.h"

#include "AppConfigLoader.h"
#include "Logger.h"
#include "WxQyGetTokenResp.h"
#include "WxQyTokenRefresher.h"

// 获取最新的AccessToken
std::string WxQyApi::getAccessToken() {
    // 全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    // 创建 HTTPS 客户端
    httplib::SSLClient client(config.wechatApi.host, config.wechatApi.port);

    // 设置连接超时时间（5秒）
    client.set_connection_timeout(5, 0);

    // 设置读取超时时间（5秒）
    client.set_read_timeout(5, 0);

    // 构造 URL 路径
    std::string url_path = config.wechatApi.getTokenPath + "?corpid=" + config.wechatAccount.corpId +
                           "&corpsecret=" + config.wechatAccount.corpSecret;

    // 发送Get请求
    auto res = client.Get(url_path);

    // 获取请求结果
    if (res) {
        if (res->status == 200) {
            try {
                // JSON反序列化
                WxQyGetTokenResp response = json::parse(res->body);
                if (response.GetErrCode() == 0) {
                    std::string access_token = response.GetAccessToken();
                    LOG_DEBUG("Get Access Token Success: %s", access_token.c_str());
                    return access_token;
                } else {
                    LOG_ERROR("Get Access Token Failed: %s", response.GetErrMsg().c_str());
                }
            } catch (const std::exception& e) {
                LOG_ERROR("Json Parse Failed: %s", e.what());
            }
        } else {
            LOG_ERROR("HTTPS Get Request Status: %d, URL: %s, Response: %s", res->status, url_path.c_str(),
                      res->body.c_str());
        }
    } else {
        LOG_ERROR("HTTPS Get Request Failed, URL: %s, Error Code: %d", url_path.c_str(), static_cast<int>(res.error()));
    }

    return "";
}

// 发送应用消息
void WxQyApi::sendMessage(const WxQySendMsgReq& req) {
    // 全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    // 创建 HTTPS 客户端
    httplib::SSLClient client(config.wechatApi.host, config.wechatApi.port);

    // 设置连接超时时间（5秒）
    client.set_connection_timeout(5, 0);

    // 设置读取超时时间（5秒）
    client.set_read_timeout(5, 0);

    // 构造 URL 路径
    std::string url_path =
        config.wechatApi.sendMsgPath + "?access_token=" + WxQyTokenRefresher::getInstance().getLocalAccessToken();

    // 构造JSON消息
    std::string json_body;

    // JSON序列化
    try {
        json j = req;
        json_body = j.dump();
        LOG_DEBUG("HTTPS Post Data: %s", json_body.c_str());
    } catch (const std::exception& e) {
        LOG_ERROR("Json Dump Failed: %s", e.what());
        return;
    }

    // 发送Post请求
    auto res = client.Post(url_path, json_body, "application/json");

    // 获取请求结果
    if (res) {
        LOG_DEBUG("HTTPS Post Request Status: %d, URL: %s, Response: %s", res->status, url_path.c_str(),
                  res->body.c_str());
    } else {
        LOG_ERROR("HTTPS Get Request Failed, URL: %s, Error Code: %d", url_path.c_str(), static_cast<int>(res.error()));
    }
}