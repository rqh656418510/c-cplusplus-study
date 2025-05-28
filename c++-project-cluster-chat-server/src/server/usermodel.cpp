#include "usermodel.hpp"

#include <muduo/base/Logging.h>

#include <iostream>
#include <string>

#include "db.h"

using namespace std;

// 插入用户信息
bool UserModel::insert(User& user) {
    char sql[1024] = {0};

    // 拼接 SQL 语句
    sprintf(sql, "insert into user(name, password, state) values('%s', '%s', '%s')", user.getName().c_str(),
            user.getPassword().c_str(), user.getState().c_str());

    // 执行 SQL 语句
    MySQL mysql;
    if (mysql.connect() && mysql.update(sql)) {
        // 获取插入新用户的ID
        uint64_t id = mysql_insert_id(mysql.getConnection());
        // 设置新用户的 ID
        user.setId(id);
        return true;
    }

    return false;
}

// 更新用户信息
bool UserModel::update(User& user) {
    return false;
}