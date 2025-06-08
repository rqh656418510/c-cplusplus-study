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

    // 查找好友关系
    Friend select(int userid, int friendid);
};

#endif  // FRIENDMODEL_H