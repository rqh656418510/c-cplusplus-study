#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include <vector>

#include "friend.hpp"
#include "user.hpp"

// Friend 表的数据操作类
class FriendModel {
public:
    // 添加好友关系
    bool insert(int userid, int friendid);

    // 查找好友列表
    vector<User> select(int userid);
};

#endif  // FRIENDMODEL_H