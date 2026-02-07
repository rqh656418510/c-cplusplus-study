#pragma once

#include <string>

#include "json.hpp"

// 类型重定义
using json = nlohmann::json;

// 企业微信发送应用消息的响应结果
class WxQySendMsgResp {
public:
    // 默认构造函数
    WxQySendMsgResp() = default;

    // ---------- Getter ----------
    int GetErrCode() const {
        return errcode_;
    }
    const std::string& GetErrMsg() const {
        return errmsg_;
    }
    const std::string& GetInvalidUser() const {
        return invaliduser_;
    }
    const std::string& GetInvalidParty() const {
        return invalidparty_;
    }
    const std::string& GetInvalidTag() const {
        return invalidtag_;
    }
    const std::string& GetUnlicensedUser() const {
        return unlicenseduser_;
    }
    const std::string& GetMsgId() const {
        return msgid_;
    }
    const std::string& GetResponseCode() const {
        return response_code_;
    }

    // ---------- Setter ----------
    void SetErrCode(int errcode) {
        errcode_ = errcode;
    }
    void SetErrMsg(const std::string& errmsg) {
        errmsg_ = errmsg;
    }
    void SetInvalidUser(const std::string& v) {
        invaliduser_ = v;
    }
    void SetInvalidParty(const std::string& v) {
        invalidparty_ = v;
    }
    void SetInvalidTag(const std::string& v) {
        invalidtag_ = v;
    }
    void SetUnlicensedUser(const std::string& v) {
        unlicenseduser_ = v;
    }
    void SetMsgId(const std::string& msgid) {
        msgid_ = msgid;
    }
    void SetResponseCode(const std::string& code) {
        response_code_ = code;
    }

    // 辅助判断
    bool IsSuccess() const {
        return errcode_ == 0;
    }

private:
    int errcode_{-1};
    std::string errmsg_;
    std::string invaliduser_;
    std::string invalidparty_;
    std::string invalidtag_;
    std::string unlicenseduser_;
    std::string msgid_;
    std::string response_code_;
};

// JSON 反序列化
inline void from_json(const json& j, WxQySendMsgResp& msg) {
    if (j.contains("errcode")) msg.SetErrCode(j.at("errcode").get<int>());
    if (j.contains("errmsg")) msg.SetErrMsg(j.at("errmsg").get<std::string>());
    if (j.contains("invaliduser")) msg.SetInvalidUser(j.at("invaliduser").get<std::string>());
    if (j.contains("invalidparty")) msg.SetInvalidParty(j.at("invalidparty").get<std::string>());
    if (j.contains("invalidtag")) msg.SetInvalidTag(j.at("invalidtag").get<std::string>());
    if (j.contains("unlicenseduser")) msg.SetUnlicensedUser(j.at("unlicenseduser").get<std::string>());
    if (j.contains("msgid")) msg.SetMsgId(j.at("msgid").get<std::string>());
    if (j.contains("response_code")) msg.SetResponseCode(j.at("response_code").get<std::string>());
}
