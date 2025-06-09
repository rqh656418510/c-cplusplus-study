#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include <vector>

#include "group.hpp"
#include "json.hpp"
#include "usermodel.hpp"

// 类型重定义
using json = nlohmann::json;

// Group 表的数据操作类
class GroupModel {
public:
    // 新增群组
    bool insert(Group& group);

    // 查询所有群组
    vector<Group> list();

    // 查询指定的群组
    Group select(int id);

    // 删除群组
    bool remove(int id);
};

// JSON 序列化
inline void to_json(json& j, const Group& group) {
    j["id"] = group.getId();
    j["groupname"] = group.getGroupName();
    j["groupdesc"] = group.getGroupDesc();
    j["groupusers"] = group.getUsers();
}

// JSON 反序列化
inline void from_json(const json& j, Group& group) {
    if (j.contains("id")) group.setId(j.at("id").get<int>());
    if (j.contains("groupname")) group.setGroupName(j.at("groupname").get<string>());
    if (j.contains("groupdesc")) group.setGroupDesc(j.at("groupdesc").get<string>());
}

#endif  // GROUPMODEL_H