#ifndef OFFLINEMESSAGEMODEL_H
#define OFFLINEMESSAGEMODEL_H

#include <json.hpp>
#include <vector>

#include "offlinemessage.hpp"

// 类型重定义
using json = nlohmann::json;

// OfflineMessage 表的数据操作类
class OfflineMessageModel {
public:
    // 新增离线消息
    bool insert(const OfflineMessage& message);

    // 删除用户的所有离线消息
    bool remove(int userId);

    // 获取用户的所有离线消息
    vector<OfflineMessage> select(int userId);
};

// JSON 序列化
inline void to_json(json& j, const OfflineMessage& msg) {
    j["message"] = msg.getMessage();
    j["createtime"] = msg.getCreateTime();
}

// JSON 反序列化
inline void from_json333(const json& j, OfflineMessage msg) {
    msg.setMessage(j.at("message").get<string>());
    msg.setCreateTime(j.at("createtime").get<long>());
}

#endif  // OFFLINEMESSAGEMODEL_H