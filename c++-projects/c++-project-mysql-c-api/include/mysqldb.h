#ifndef MYSQLDB_H
#define MYSQLDB_H

#include <mysql/mysql.h>

#include <iostream>
#include <string>

// 数据库操作类
class MySQL {
public:
    // 初始化数据库连接
    MySQL();

    // 释放数据库连接
    ~MySQL();

    // 连接数据库
    bool connect();

    // 更新操作
    bool update(std::string sql);

    // 查询操作
    MYSQL_RES *query(std::string sql);

    // 获取数据库连接
    MYSQL *getConnection();

private:
    MYSQL *_conn;  // 数据库连接（非线程安全）
};

#endif  // MYSQLDB_H
