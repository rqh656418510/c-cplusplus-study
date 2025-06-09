/**
 * MySQL 增删改查操作的定义
 */

#pragma once

#include <iostream>
#include <vector>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <chrono>
#include "public.h"

using namespace std;
using namespace sql;

typedef chrono::system_clock::time_point time_point;

// MySQL 数据库操作类
class MysqlConnection {

public:
    MysqlConnection();

    ~MysqlConnection();

public:

    bool execute(const char *sql);

    int executeUpdate(const char *sql);

    unique_ptr<ResultSet> query(const char *query, const vector<string> parameters);

    bool connect(const string host, const string username, const string password, const string dbname);

    void refreshAliveTime();

    long getAliveTime() const;

private:
    string _host;                           // MySQL 连接地址
    string _username;                       // MySQL 用户名
    string _password;                       // MySQL 密码
    string _dbname;                         // MySQL 数据库
    Driver *_driver;                        // MySQL 驱动
    Connection *_connection;                // MySQL 连接
    time_point _aliveTime;                  // 记录连接进入空闲状态后的起始存活时间点
};