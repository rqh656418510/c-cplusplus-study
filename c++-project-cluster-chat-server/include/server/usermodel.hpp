#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"

// User 表的数据操作类
class UserModel {
public:
    // 插入用户信息
    bool insert(User& user);

    // 更新用户信息
    bool update(User& user);
};

#endif  // USERMODEL_H