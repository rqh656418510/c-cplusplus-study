#ifndef USERMODEL_H
#define USERMODEL_H

#include "json.hpp"
#include "user.hpp"

// 类型重定义
using json = nlohmann::json;

// User 表的数据操作类
class UserModel {
public:
    // 根据用户ID查询用户
    User select(int id);

    // 根据用户名查询用户
    User selectByName(string name);

    // 新增用户
    bool insert(User& user);

    // 更新用户的登录状态
    bool updateState(User& user);

    // 重置所有用户的登录状态
    bool resetState();
};

// JSON 序列化
inline void to_json(json& j, const User& user) {
    j["id"] = user.getId();
    j["name"] = user.getName();
    j["state"] = user.getState();
}

// JSON 反序列化
inline void from_json(const json& j, User& user) {
    if (j.contains("id")) user.setId(j.at("id").get<int>());
    if (j.contains("name")) user.setName(j.at("name").get<string>());
    if (j.contains("state")) user.setState(j.at("state").get<string>());
}

#endif  // USERMODEL_H