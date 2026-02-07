#pragma once

#include <mysql/mysql.h>

#include <atomic>
#include <chrono>
#include <ctime>
#include <string>

// 类型重定义
using time_point = std::chrono::system_clock::time_point;

// MySQL数据库操作类
class MySqlConnection {
public:
    // 初始化数据库连接
    MySqlConnection();

    // 关闭数据库连接
    ~MySqlConnection();

    // 删除拷贝构造函数
    MySqlConnection(const MySqlConnection&) = delete;

    // 删除赋值运算操作符
    MySqlConnection& operator=(const MySqlConnection&) = delete;

    // 连接数据库
    bool connect(const std::string& ip, unsigned short port, const std::string& username, const std::string& password,
                 const std::string& dbname);

    // 执行更新操作（insert、delete、update）
    bool update(const std::string& sql);

    // 执行查询操作（select）
    MYSQL_RES* query(const std::string& sql);

    // 刷新连接进入空闲状态后的起始存活时间点
    void refreshAliveTime();

    // 获取连接的空闲存活时间（单位毫秒）
    long long getAliveTime() const;

private:
    MYSQL* conn_;                       // 表示和MySQL Server的一条连接
    std::atomic<long long> aliveTime_;  // 记录进入空闲状态后的起始存活时间
};