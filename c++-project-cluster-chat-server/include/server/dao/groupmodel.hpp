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
    vector<Group> select();

    // 删除群组
    bool remove(int id);
};

// JSON 序列化
inline void to_json(json& j, const Group& msg) {
    j["id"] = msg.getId();
    j["groupname"] = msg.getGroupName();
    j["groupdesc"] = msg.getGroupDesc();
    j["groupusers"] = msg.getUsers();
}

#endif  // GROUPMODEL_H