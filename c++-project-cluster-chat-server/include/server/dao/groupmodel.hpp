#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include <vector>

#include "group.hpp"

// Group 表的数据操作类
class GroupModel {
    // 新增群组
    bool insert(Group& group);

    // 查询所有群组
    vector<Group> select();

    // 删除群组
    bool remove(int id);
};

#endif  // GROUPMODEL_H