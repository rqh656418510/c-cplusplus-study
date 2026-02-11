#pragma once

#include <mysql/mysql.h>

#include <atomic>
#include <chrono>
#include <ctime>
#include <string>

#include "NonCopyable.h"

// 类型重定义
using time_point = std::chrono::system_clock::time_point;

// MySQL数据库操作类
class MySqlConnection : NonCopyable {
public:
    // 初始化数据库连接
    MySqlConnection();

    // 关闭数据库连接
    ~MySqlConnection();

    // 连接数据库
    bool connect(const std::string& ip, unsigned short port, const std::string& username, const std::string& password,
                 const std::string& dbname);

    // 执行更新操作（insert、delete、update）
    bool update(const std::string& sql);

    // 执行查询操作（select）
    MYSQL_RES* query(const std::string& sql);

    // 为连接发送心跳
    bool sendHeartbeat();

    // 刷新连接进入空闲状态的时间戳
    void refreshIdleStartTime();

    // 获取连接进入空闲状态的总时长（单位毫秒）
    long long getIdleTotalTimes() const;

    // 获取连接上次发送心跳距今的时间间隔（毫秒）
    long long getLastHeartbeatIntervalTime() const;

    // 刷新连接上次发送心跳的时间戳
    void refreshLastHeartbeatTime();

private:
    MYSQL* conn_;                               // 表示和MySQL Server的一条连接（非线程安全）
    std::atomic<long long> idleStartTime_;      // 记录连接进入空闲状态的时间戳（单位毫秒）
    std::atomic<long long> lastHeartbeatTime_;  // 记录连接上次发送心跳的时间戳（单位毫秒）
};