#pragma once

#include <string>

#include "json.hpp"

// 类型重定义
using json = nlohmann::json;

// 企业微信获取AccessToken的响应结果
class WxQyGetTokenResp {
public:
    // 默认构造函数
    WxQyGetTokenResp() = default;

    // ---------- Getter ----------
    int GetErrCode() const {
        return errcode_;
    }
    int GetExpiresIn() const {
        return expires_in_;
    }
    const std::string& GetErrMsg() const {
        return errmsg_;
    }
    const std::string& GetAccessToken() const {
        return access_token_;
    }

    // ---------- Setter ----------
    void SetErrCode(int errcode) {
        errcode_ = errcode;
    }
    void SetExpiresIn(int expiresIn) {
        expires_in_ = expiresIn;
    }
    void SetErrMsg(const std::string& errmsg) {
        errmsg_ = errmsg;
    }
    void SetAccessToken(const std::string& token) {
        access_token_ = token;
    }

    // 辅助方法
    bool IsSuccess() const {
        return errcode_ == 0 && !access_token_.empty();
    }

private:
    int errcode_{-1};
    int expires_in_{0};
    std::string errmsg_;
    std::string access_token_;
};

// JSON 反序列化
inline void from_json(const json& j, WxQyGetTokenResp& msg) {
    if (j.contains("errcode")) msg.SetErrCode(j.at("errcode").get<int>());
    if (j.contains("expires_in")) msg.SetExpiresIn(j.at("expires_in").get<int>());
    if (j.contains("errmsg")) msg.SetErrMsg(j.at("errmsg").get<std::string>());
    if (j.contains("access_token")) msg.SetAccessToken(j.at("access_token").get<std::string>());
}