#ifndef USERDAO_H
#define USERDAO_H

#include <iostream>
#include <string>

#include "user.h"

// User 表的数据操作类
class UserDao {
public:
    // 根据用户ID查询用户
    User select(int id);

    // 根据用户名查询用户
    User selectByName(std::string name);

    // 新增用户
    bool insert(User& user);

    // 更新用户的登录状态
    bool updateState(User& user);
};

#endif  // USERDAO_H
