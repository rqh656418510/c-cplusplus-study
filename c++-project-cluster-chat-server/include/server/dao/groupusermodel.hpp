#ifndef GROUPUSERMODEL_H
#define GROUPUSERMODEL_H

#include <vector>

#include "group.hpp"
#include "groupuser.hpp"
#include "user.hpp"

// GroupUser 表的数据操作类
class GroupUserModel {
public:
    // 添加用户与用户组关联
    bool insert(const GroupUser& groupUser);

    // 查询用户拥有的所有群组
    vector<Group> select(int userId);

    // 根据指定的 groupId 查询群组用户的 userId 列表，并排除 excludeUserId
    vector<User> selectGroupUsers(int groupId, int excludeUserId);
};

#endif  // GROUPUSERMODEL_H