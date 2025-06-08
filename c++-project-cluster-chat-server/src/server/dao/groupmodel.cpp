#include "groupmodel.hpp"

#include <string>

#include "db.hpp"

// 新增群组
bool GroupModel::insert(Group& group) {
    char sql[1024] = {0};

    // 拼接 SQL 语句
    sprintf(sql, "insert into allgroup(groupname, groupdesc) values('%s', '%s')", group.getGroupName().c_str(),
            group.getGroupDesc().c_str());

    // 执行 SQL 语句
    MySQL mysql;
    if (mysql.connect() && mysql.update(sql)) {
        // 获取插入新群组的ID
        uint64_t id = mysql_insert_id(mysql.getConnection());
        // 设置新群组的 ID
        group.setId(id);
        return true;
    }

    return false;
}

// 查询所有群组
vector<Group> GroupModel::select() {
    char sql[1024] = {0};

    // 查询结果
    vector<Group> result;

    // 拼接 SQL 语句
    sprintf(sql, "select id, groupname, groupdesc from allgroup");

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

    return result;
}

// 删除群组
bool GroupModel::remove(int id) {
    char sql[1024] = {0};

    // 拼接 SQL 语句
    sprintf(sql, "delete from allgroup where id = %d", id);

    // 执行 SQL 语句
    MySQL mysql;
    if (mysql.connect() && mysql.update(sql)) {
        return true;
    }

    return false;
}