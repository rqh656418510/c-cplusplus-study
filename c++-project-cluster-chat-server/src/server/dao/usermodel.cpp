#include "usermodel.hpp"

#include <muduo/base/Logging.h>

#include <iostream>
#include <string>

#include "db.hpp"

using namespace std;

// 根据用户ID查询用户
User UserModel::select(int id) {
    char sql[1024] = {0};

    // 拼接 SQL 语句
    sprintf(sql, "select id, name, password, state from user where id = %d", id);

    // 执行查询操作
    MySQL mysql;
    if (mysql.connect()) {
        // 执行 SQL 语句
        MYSQL_RES* res = mysql.query(sql);
        if (res != nullptr && mysql_num_rows(res) > 0) {
            // 获取查询结果
            MYSQL_ROW row = mysql_fetch_row(res);
            // 封装返回的数据
            User user;
            user.setId(atoi(row[0]));
            user.setName(row[1]);
            user.setPassword(row[2]);
            user.setState(row[3]);
            // 释放资源
            mysql_free_result(res);
            return user;
        }
    }

    return User();
}

// 根据用户名查询用户
User UserModel::selectByName(string name) {
    char sql[1024] = {0};

    // 拼接 SQL 语句
    sprintf(sql, "select id, name, password, state from user where name = '%s'", name.c_str());

    // 执行查询操作
    MySQL mysql;
    if (mysql.connect()) {
        // 执行 SQL 语句
        MYSQL_RES* result = mysql.query(sql);
        if (result != nullptr && mysql_num_rows(result) > 0) {
            // 获取查询结果
            MYSQL_ROW row = mysql_fetch_row(result);
            // 封装返回的数据
            User user;
            user.setId(atoi(row[0]));
            user.setName(row[1]);
            user.setPassword(row[2]);
            user.setState(row[3]);
            // 释放资源
            mysql_free_result(result);
            return user;
        }
    }

    return User();
}

// 新增用户
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

// 更新用户的登录状态
bool UserModel::updateState(User& user) {
    char sql[1024] = {0};

    // 拼接 SQL 语句
    sprintf(sql, "update user set state = '%s' where id = %d", user.getState().c_str(), user.getId());

    // 执行 SQL 语句
    MySQL mysql;
    if (mysql.connect() && mysql.update(sql)) {
        return true;
    }

    return false;
}

// 重置所有用户的登录状态
bool UserModel::resetState() {
    char sql[1024] = {0};

    // 拼接 SQL 语句
    sprintf(sql, "update user set state = 'offline' where state = 'online'");

    // 执行 SQL 语句
    MySQL mysql;
    if (mysql.connect() && mysql.update(sql)) {
        return true;
    }

    return false;
}
