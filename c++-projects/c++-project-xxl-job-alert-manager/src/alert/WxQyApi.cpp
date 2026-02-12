#include "WxQyApi.h"

#include <curl/curl.h>

#include <sstream>

#include "AppConfigLoader.h"
#include "CurlHelper.h"
#include "Logger.h"
#include "WxQyGetTokenResp.h"
#include "WxQySendMsgResp.h"
#include "WxQyTokenRefresher.h"

// 获取最新的AccessToken
std::string WxQyApi::getAccessToken() {
    // 全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    // 构造URL
    std::string url = "https://" + config.wxQyApi.host + config.wxQyApi.getTokenPath +
                      "?corpid=" + config.wxQyAccount.corpId + "&corpsecret=" + config.wxQyAccount.corpSecret;

    // 创建Curl对象
    CURL* curl = curl_easy_init();
    if (!curl) {
        LOG_ERROR("Curl Init Failed");
        return "";
    }

    std::string response_str;

    // 设置Curl选项
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_str);  // 写回调的目标对象
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);               // 设置请求超时时间为5秒（单位：秒）
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);        // 启用对服务器SSL证书的验证
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);  // 验证服务器证书中的主机名是否与请求URL匹配

    // 发送GET请求
    CURLcode res = curl_easy_perform(curl);
    long resp_http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resp_http_code);

    // 检查请求是否成功
    if (res != CURLE_OK) {
        LOG_ERROR("Https get request failed: %s, URL: %s", curl_easy_strerror(res), url.c_str());
        curl_easy_cleanup(curl);
        return "";
    }

    if (resp_http_code != 200) {
        LOG_ERROR("Https get request status: %ld, URL: %s, Response: %s", resp_http_code, url.c_str(),
                  response_str.c_str());
        curl_easy_cleanup(curl);
        return "";
    }

    // JSON反序列化，判断AccessToken获取结果
    try {
        WxQyGetTokenResp response = json::parse(response_str);
        if (response.GetErrCode() == 0) {
            std::string access_token = response.GetAccessToken();
            LOG_DEBUG("Get access token success by https: %s", access_token.c_str());
            curl_easy_cleanup(curl);
            return access_token;
        } else {
            LOG_ERROR("Get access token failed by https: %s", response.GetErrMsg().c_str());
        }
    } catch (const std::exception& e) {
        LOG_ERROR("Json parse failed: %s", e.what());
    }

    // 清理资源
    curl_easy_cleanup(curl);

    return "";
}

// 发送应用消息
bool WxQyApi::sendMessage(const WxQySendMsgReq& req) {
    // 全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    // 构造URL
    std::string url = "https://" + config.wxQyApi.host + config.wxQyApi.sendMsgPath +
                      "?access_token=" + WxQyTokenRefresher::getInstance().getLocalAccessToken();

    // 构造JSON消息
    std::string json_body;
    try {
        json j = req;
        json_body = j.dump();
        LOG_DEBUG("Https post data: %s", json_body.c_str());
    } catch (const std::exception& e) {
        LOG_ERROR("Json dump failed: %s", e.what());
        return false;
    }

    // 创建Curl对象
    CURL* curl = curl_easy_init();
    if (!curl) {
        LOG_ERROR("Curl Init Failed");
        return false;
    }

    std::string response_str;

    // 设置HTTP Header
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // 设置Curl选项
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_str);  // 写回调的目标对象
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);               // 设置请求超时时间为5秒（单位：秒）
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);        // 启用对服务器SSL证书的验证
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);  // 验证服务器证书中的主机名是否与请求URL匹配

    // 发送POST请求
    CURLcode res = curl_easy_perform(curl);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    // 检查请求是否成功
    if (res != CURLE_OK) {
        LOG_ERROR("Https post request failed: %s, URL: %s", curl_easy_strerror(res), url.c_str());
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return false;
    }

    LOG_DEBUG("Https post request status: %ld, URL: %s, Response: %s", http_code, url.c_str(), response_str.c_str());

    // JSON反序列化，判断消息发送结果
    try {
        WxQySendMsgResp resp = json::parse(response_str);
        if (resp.GetErrCode() == 0) {
            LOG_DEBUG("Send message success by https");
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            return true;
        } else {
            LOG_ERROR("Send message failed by https: %s", resp.GetErrMsg().c_str());
        }
    } catch (const std::exception& e) {
        LOG_ERROR("Json parse failed: %s", e.what());
    }

    // 清理资源
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return false;
}