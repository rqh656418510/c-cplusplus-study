/**
 * MySQL 增删改查操作的定义
 */

#pragma once

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>

#include <atomic>
#include <chrono>
#include <iostream>
#include <vector>

#include "public.h"

using namespace std;
using namespace sql;

// MySQL 数据库操作类
class MysqlConnection {
public:
    // 构造函数
    MysqlConnection();

    // 析构函数
    ~MysqlConnection();

    // 删除拷贝构造函数
    MysqlConnection(const MysqlConnection &) = delete;

    // 删除赋值运算操作符
    MysqlConnection &operator=(const MysqlConnection &) = delete;

    // 执行任何 SQL 语句，返回一个 bool 值，表明执行该 SQL 语句是否返回了 ResultSet
    bool execute(const char *sql);

    // 执行 INSERT、UPDATE 或 DELETE 语句以及 SQL DDL（数据定义语言）语句
    int executeUpdate(const char *sql);

    // 基于 SQL 的预编译机制，执行查询单个结果集（ResultSet）的 SQL 语句
    unique_ptr<ResultSet> query(const char *query, const vector<string> parameters);

    // 连接数据库
    bool connect(const string &host, const string &username, const string &password, const string &dbname);

    // 刷新连接进入空闲状态的时间戳
    void refreshIdleStartTime();

    // 获取连接进入空闲状态的总时长（单位毫秒）
    long long getIdleTotalTimes() const;

private:
    string _host;                       // MySQL 连接地址
    string _username;                   // MySQL 用户名
    string _password;                   // MySQL 密码
    string _dbname;                     // MySQL 数据库
    Driver *_driver;                    // MySQL 驱动
    Connection *_connection;            // MySQL 连接（非线程安全）
    std::atomic<long long> _idleStartTime;  // 记录连接进入空闲状态的时间戳（单位毫秒）
};