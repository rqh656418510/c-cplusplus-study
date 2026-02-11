#include "MySqlConnection.h"

#include <exception>
#include <iostream>

#include "Logger.h"

// 初始化数据库连接
MySqlConnection::MySqlConnection() {
    conn_ = mysql_init(nullptr);
}

// 关闭数据库连接
MySqlConnection::~MySqlConnection() {
    try {
        if (conn_ != nullptr) {
            // 关闭连接
            mysql_close(conn_);
        }
    } catch (const std::exception& e) {
        LOG_ERROR("Failed to close connection, exception: %s", e.what());
    } catch (...) {
        LOG_ERROR("Failed to close connection, unknow exception");
    }
}

// 连接数据库
bool MySqlConnection::connect(const std::string& ip, unsigned short port, const std::string& username,
                              const std::string& password, const std::string& dbname) {
    // 旧版本的MySQL，需要关闭自动重连的标记（生产环境不应依赖MySQL的自动重连机制，应由连接池统一管理连接的创建、重连与关闭等）
    // bool reconnect = false;

    // 配置连接
    // mysql_options(conn_, MYSQL_OPT_RECONNECT, &reconnect);

    // 发起连接
    MYSQL* p =
        mysql_real_connect(conn_, ip.c_str(), username.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);

    if (p == nullptr) {
        LOG_ERROR("Connect mysql [%s:%d] failed", ip.c_str(), port);
        LOG_ERROR("%s", mysql_error(conn_));
        return false;
    }

    // C和C++代码默认的编码字符是ASCII，如果不设置，从MySQL查询到的中文内容可能会显示乱码
    if (mysql_set_character_set(conn_, "utf8mb4") != 0) {
        LOG_ERROR("Set charset failed: %s", mysql_error(conn_));
        return false;
    }

    LOG_DEBUG("Connect mysql [%s:%d] success", ip.c_str(), port);
    return true;

    return p != nullptr;
}

// 执行更新操作（insert、delete、update）
bool MySqlConnection::update(const std::string& sql) {
    LOG_DEBUG(sql.c_str());

    if (mysql_query(conn_, sql.c_str())) {
        LOG_ERROR("%s:%d %s execute failed!", __FILE__, __LINE__, sql.c_str());
        LOG_ERROR(mysql_error(conn_));
        return false;
    }

    return true;
}

// 执行查询操作（select）
MYSQL_RES* MySqlConnection::query(const std::string& sql) {
    LOG_DEBUG(sql.c_str());

    if (mysql_query(conn_, sql.c_str())) {
        LOG_ERROR("%s:%d %s execute failed!", __FILE__, __LINE__, sql.c_str());
        LOG_ERROR(mysql_error(conn_));
        return nullptr;
    }

    return mysql_store_result(conn_);
}

// 为连接发送心跳
bool MySqlConnection::sendHeartbeat() {
    if (conn_ == nullptr) {
        return false;
    }

    // 发送心跳，0 → 成功（连接可用），非 0 → 失败（连接断开或异常）
    if (mysql_ping(conn_) == 0) {
        return true;
    }

    // 打印日志信息
    LOG_ERROR("Connection send heartbeat failed: %s", mysql_errno(conn_));

    return false;
}

// 刷新连接进入空闲状态的时间戳
void MySqlConnection::refreshIdleStartTime() {
    auto now = std::chrono::steady_clock::now();
    long long now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    idleStartTime_.store(now_ms, std::memory_order_relaxed);
}

// 获取连接进入空闲状态的总时长（单位毫秒）
long long MySqlConnection::getIdleTotalTimes() const {
    auto now = std::chrono::steady_clock::now();
    long long now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return static_cast<long>(now_ms - idleStartTime_.load(std::memory_order_relaxed));
}

// 刷新连接上次发送心跳的时间戳
void MySqlConnection::refreshLastHeartbeatTime() {
    auto now = std::chrono::steady_clock::now();
    long long now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    lastHeartbeatTime_.store(now_ms, std::memory_order_relaxed);
}

// 获取连接上次发送心跳的时间戳（单位毫秒）
long long MySqlConnection::getLastHeartbeatIntervalTime() const {
    auto now = std::chrono::steady_clock::now();
    long long now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return static_cast<long>(now_ms - lastHeartbeatTime_.load(std::memory_order_relaxed));
}