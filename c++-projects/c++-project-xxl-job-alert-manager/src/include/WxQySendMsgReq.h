#pragma once

#include <string>

#include "json.hpp"

// 类型重定义
using json = nlohmann::json;

// 企业微信发送应用消息的请求参数
class WxQySendMsgReq {
public:
    // 默认构造函数
    WxQySendMsgReq() = default;

    // ---------- Getter ----------
    std::string getTouser() const {
        return touser_;
    }
    std::string getMsgtype() const {
        return msgtype_;
    }
    int getAgentid() const {
        return agentid_;
    }
    std::string getContent() const {
        return content_;
    }
    int getSafe() const {
        return safe_;
    }

    // ---------- Setter ----------
    void setTouser(const std::string& touser) {
        touser_ = touser;
    }
    void setMsgtype(const std::string& msgtype) {
        msgtype_ = msgtype;
    }
    void setAgentid(int agentid) {
        agentid_ = agentid;
    }
    void setContent(const std::string& content) {
        content_ = content;
    }
    void setSafe(int safe) {
        safe_ = safe;
    }

private:
    std::string touser_;   // 接收用户
    std::string msgtype_;  // 消息类型
    int agentid_{0};       // 企业应用 ID
    std::string content_;  // 文本内容
    int safe_{0};          // 是否保密 0/1
};

// JSON 序列化
inline void to_json(json& j, const WxQySendMsgReq& msg) {
    j["touser"] = msg.getTouser();
    j["msgtype"] = msg.getMsgtype();
    j["agentid"] = msg.getAgentid();
    j["text"]["content"] = msg.getContent();
    j["safe"] = msg.getSafe();
}