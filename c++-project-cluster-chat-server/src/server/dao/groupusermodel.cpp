#include "groupusermodel.hpp"

#include "db.h"

// 添加用户与群组的关联信息
bool GroupUserModel::insert(const GroupUser& groupUser) {
    char sql[1024] = {0};

    // 拼接 SQL 语句
    sprintf(sql, "insert into groupuser(groupid, userid, grouprole) values(%d, %d, '%s')", groupUser.getGroupId(),
            groupUser.getUserId(), groupUser.getGroupRole().c_str());

    // 执行 SQL 语句
    MySQL mysql;
    if (mysql.connect() && mysql.update(sql)) {
        return true;
    }

    return false;
}

// 查询用户拥有的所有群组
vector<Group> GroupUserModel::select(int userId) {
    char sql[1024] = {0};

    // 查询结果
    vector<Group> result;

    // 拼接 SQL 语句
    sprintf(sql,
            "select g.id, g.groupname, g.groupdesc from groupuser gu inner join allgroup g on gu.groupid = g.id where "
            "gu.userid = %d",
            userId);

    // 执行查询操作
    MySQL mysql;
    if (mysql.connect()) {
        // 执行 SQL 语句
        MYSQL_RES* res = mysql.query(sql);
        if (res != nullptr && mysql_num_rows(res) > 0) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr) {
                int id = atoi(row[0]);
                string groupname = row[1];
                string groupdesc = row[2];
                result.emplace_back(id, groupname, groupdesc);
            }
        }
        // 释放资源
        mysql_free_result(res);
    }

    // 查询群组内的所有用户
    for (Group& group : result) {
        // 拼接 SQL 语句
        sprintf(sql,
                "select u.id, u.name, u.state from groupuser gu inner join user u on gu.userid = u.id where gu.groupid "
                "= %d",
                group.getId());

        // 执行 SQL 语句
        MYSQL_RES* res2 = mysql.query(sql);
        if (res2 != nullptr && mysql_num_rows(res2) > 0) {
            MYSQL_ROW row2;
            while ((row2 = mysql_fetch_row(res2)) != nullptr) {
                int id = atoi(row2[0]);
                string name = row2[1];
                string state = row2[2];
                group.getUsers().emplace_back(id, name, state);
            }
        }
        // 释放资源
        mysql_free_result(res2);
    }

    return result;
}

// 根据指定的 groupId，查询该群组的用户列表，并排除 excludeUserId
vector<User> GroupUserModel::selectGroupUsers(int groupId, int excludeUserId) {
    char sql[1024] = {0};

    // 查询结果
    vector<User> result;

    // 拼接 SQL 语句
    sprintf(sql,
            "select u.id, u.name, u.state from groupuser gu inner join user u on gu.userid = u.id where gu.groupid = "
            "%d and gu.userid != %d",
            groupId, excludeUserId);

    // 执行查询操作
    MySQL mysql;
    if (mysql.connect()) {
        // 执行 SQL 语句
        MYSQL_RES* res = mysql.query(sql);
        if (res != nullptr && mysql_num_rows(res) > 0) {
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

    return result;
}
