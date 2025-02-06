/**
 * MySQL 增删改查操作的实现
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
#include "public.h"

using namespace std;
using namespace sql;

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

private:
    string _host;                           // MySQL 连接地址
    string _username;                       // MySQL 用户名
    string _password;                       // MySQL 密码
    string _dbname;                         // MySQL 数据库
    Driver *_driver;                        // MySQL 驱动
    unique_ptr<Connection> _connection;     // MySQL 连接

};