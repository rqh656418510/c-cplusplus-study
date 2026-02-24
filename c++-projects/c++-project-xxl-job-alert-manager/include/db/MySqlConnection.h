#pragma once

#include <mysql/errmsg.h>
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

    // 发送Ping指令
    bool ping() const;

    // 为连接发送心跳
    bool sendHeartbeat();

    // 判断连接是否已损坏
    bool isBrokened() const;

    // 刷新连接上次使用的时间戳
    void refreshLastUsedTime();

    // 获取连接上次使用距今的时间间隔（毫秒）
    long long getLastUsedIntervalTime() const;

    // 刷新连接进入空闲状态的时间戳
    void refreshIdleStartTime();

    // 获取连接进入空闲状态的总时长（单位毫秒）
    long long getIdleTotalTimes() const;

    // 刷新连接上次发送心跳的时间戳
    void refreshLastHeartbeatTime();

    // 获取连接上次发送心跳距今的时间间隔（毫秒）
    long long getLastHeartbeatIntervalTime() const;

private:
    std::string ip_;        // MySQL服务器的IP地址
    unsigned short port_;   // MySQL服务器的端口
    std::string username_;  // MySQL的登录用户名
    std::string password_;  // MySQL的登录密码
    std::string dbname_;    // 连接的数据库名称

    MYSQL* conn_;                                  // 表示和MySQL Server的一条连接（非线程安全）
    std::atomic_bool brokened_{false};             // 标记连接是否已损坏
    std::atomic<long long> lastUsedTime_{0};       // 记录连接上次使用的时间戳（单位毫秒）
    std::atomic<long long> idleStartTime_{0};      // 记录连接进入空闲状态的时间戳（单位毫秒）
    std::atomic<long long> lastHeartbeatTime_{0};  // 记录连接上次发送心跳的时间戳（单位毫秒）

    // 重新建立连接
    bool reconnect();
};