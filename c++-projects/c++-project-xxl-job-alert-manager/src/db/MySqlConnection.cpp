#include "MySqlConnection.h"

#include <iostream>

#include "Logger.h"

// 初始化数据库连接
MySqlConnection::MySqlConnection() {
    conn_ = mysql_init(nullptr);
}

// 关闭数据库连接
MySqlConnection::~MySqlConnection() {
    if (conn_ != nullptr) {
        mysql_close(conn_);
    }
}

// 连接数据库
bool MySqlConnection::connect(const std::string& ip, unsigned short port, const std::string& username,
                              const std::string& password, const std::string& dbname) {
    MYSQL* p =
        mysql_real_connect(conn_, ip.c_str(), username.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);

    if (p != nullptr) {
        // C和C++代码默认的编码字符是ASCII，如果不设置，从MySQL查询到的中文内容可能会显示？乱码
        mysql_query(conn_, "set names utf8mb4");
        LOG_DEBUG("connect mysql [%s:%d] success!", ip.c_str(), port);
    } else {
        LOG_ERROR("connect mysql [%s:%d] failed!", ip.c_str(), port);
        LOG_ERROR(mysql_error(conn_));
    }

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

// 刷新连接进入空闲状态后的起始存活时间点
void MySqlConnection::refreshAliveTime() {
    auto now = std::chrono::steady_clock::now();
    long long now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    aliveTime_.store(now_ms, std::memory_order_relaxed);
}

// 获取连接的空闲存活时间（单位毫秒）
long long MySqlConnection::getAliveTime() const {
    auto now = std::chrono::steady_clock::now();
    long long now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return static_cast<long>(now_ms - aliveTime_.load(std::memory_order_relaxed));
}