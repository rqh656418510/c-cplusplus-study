#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"

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
};

#endif  // USERMODEL_H