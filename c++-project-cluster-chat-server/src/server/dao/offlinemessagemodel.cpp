#include "offlinemessagemodel.hpp"

#include <iostream>
#include <string>

#include "db.hpp"

using namespace std;

// 新增离线消息
bool OfflineMessageModel::insert(const OfflineMessage& message) {
    char sql[1024] = {0};

    // 拼接 SQL 语句
    sprintf(sql, "insert into offlinemessage(userid, message, createtime) values('%d', '%s', '%ld')",
            message.getUserId(), message.getMessage().c_str(), message.getCreateTime());

    // 执行 SQL 语句
    MySQL mysql;
    if (mysql.connect() && mysql.update(sql)) {
        return true;
    }

    return false;
}

// 删除用户的所有离线消息
bool OfflineMessageModel::remove(int userId) {
    char sql[1024] = {0};

    // 拼接 SQL 语句
    sprintf(sql, "delete from offlinemessage where userid = %d", userId);

    // 执行 SQL 语句
    MySQL mysql;
    if (mysql.connect() && mysql.update(sql)) {
        return true;
    }

    return false;
}

// 获取用户的所有离线消息
vector<OfflineMessage> OfflineMessageModel::select(int userId) {
    char sql[1024] = {0};

    // 查询结果
    vector<OfflineMessage> results;

    // 拼接 SQL 语句
    sprintf(sql, "select userid, message, createtime from offlinemessage where userid = %d order by createtime desc",
            userId);

    // 执行查询操作
    MySQL mysql;
    if (mysql.connect()) {
        // 执行 SQL 语句
        MYSQL_RES* res = mysql.query(sql);
        if (res != nullptr && mysql_num_rows(res) > 0) {
            // 获取所有查询结果
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr) {
                int userid = atoi(row[0]);
                string message = row[1];
                long createtime = atol(row[2]);
                results.emplace_back(userid, message, createtime);
            }
            // 释放资源
            mysql_free_result(res);
        }
    }

    // 返回查询结果
    return results;
}