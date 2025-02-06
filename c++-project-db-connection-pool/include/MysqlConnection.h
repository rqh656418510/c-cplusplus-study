/**
 * MySQL 增删改查操作的实现
 */

#pragma once

#include <vector>
#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

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
    string host;
    string username;
    string password;
    string dbname;
    Driver *driver;
    unique_ptr<Connection> connection;

};