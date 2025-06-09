#ifndef GROUPUSERMODEL_H
#define GROUPUSERMODEL_H

#include <vector>

#include "group.hpp"
#include "groupuser.hpp"
#include "user.hpp"

// GroupUser 表的数据操作类
class GroupUserModel {
public:
    // 添加用户与群组的关联信息
    bool insert(const GroupUser& groupUser);

    // 查询用户拥有的所有群组
    vector<Group> select(int userId);

    // 查询用户与群组的关联信息
    GroupUser select(int groupid, int userid);

    // 根据指定的 groupId，查询该群组的用户列表，并排除 excludeUserId
    vector<User> selectGroupUsers(int groupId, int excludeUserId);
};

#endif  // GROUPUSERMODEL_H