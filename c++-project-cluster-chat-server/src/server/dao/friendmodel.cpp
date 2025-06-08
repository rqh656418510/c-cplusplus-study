#include <friendmodel.hpp>
#include <iostream>
#include <string>

#include "db.hpp"

using namespace std;

// 添加好友关系
bool FriendModel::insert(int userid, int friendid) {
    char sql[1024] = {0};

    // 拼接 SQL 语句
    sprintf(sql, "insert into friend(userid, friendid) values(%d, %d)", userid, friendid);

    // 执行 SQL 语句
    MySQL mysql;
    if (mysql.connect() && mysql.update(sql)) {
        return true;
    }

    return false;
}

// 查找好友列表
vector<User> FriendModel::select(int userid) {
    char sql[1024] = {0};

    // 查询结果
    vector<User> result;

    // 拼接 SQL 语句
    sprintf(sql,
            "select u.id, u.name, u.state from friend f inner join user u on f.friendid = u.id where f.userid = %d",
            userid);

    // 执行 SQL 语句
    MySQL mysql;
    if (mysql.connect()) {
        MYSQL_RES* res = mysql.query(sql);
        if (res != nullptr && mysql_num_rows(res) > 0) {
            // 获取所有查询结果
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr) {
                int id = atoi(row[0]);
                string name = row[1];
                string state = row[2];
                result.emplace_back(id, name, state);
            }
        }
        // 释放资源
        mysql_free_result(res);
    }

    // 返回查询结果
    return result;
}