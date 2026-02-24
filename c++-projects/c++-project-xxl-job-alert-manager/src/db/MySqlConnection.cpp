#include "MySqlConnection.h"

#include <chrono>
#include <exception>
#include <iostream>
#include <thread>

#include "AppConfigLoader.h"
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
    // 数据库的连接信息
    ip_ = ip;
    port_ = port;
    username_ = username;
    password_ = password;
    dbname_ = dbname;

    // 旧版本的MySQL，需要关闭自动重连的标记（生产环境不应依赖MySQL的自动重连机制，应由连接池统一管理连接的创建、重连与关闭等）
    // bool reconnect = false;

    // 配置连接
    // mysql_options(conn_, MYSQL_OPT_RECONNECT, &reconnect);

    // 建立连接
    MYSQL* p = mysql_real_connect(conn_, ip_.c_str(), username_.c_str(), password_.c_str(), dbname_.c_str(), port_,
                                  nullptr, 0);

    // 判断连接是否有效
    if (p == nullptr) {
        LOG_ERROR("Connect mysql [%s:%d] failed", ip_.c_str(), port_);
        LOG_ERROR("%s", mysql_error(conn_));
        return false;
    }

    // C和C++代码默认的编码字符是ASCII，如果不设置，从MySQL查询到的中文内容可能会显示乱码
    if (mysql_set_character_set(conn_, "utf8mb4") != 0) {
        LOG_ERROR("Set charset failed: %s", mysql_error(conn_));
    }

    LOG_DEBUG("Connect mysql [%s:%d] success", ip_.c_str(), port_);

    return true;
}

// 执行更新操作（insert、delete、update）
bool MySqlConnection::update(const std::string& sql) {
    LOG_DEBUG("Execute sql: %s", sql.c_str());

    // 判断连接是否有效，无效则自动重连
    if (!conn_ && !reconnect()) {
        LOG_ERROR("%s:%d %s execute failed, connection invalid", __FILE__, __LINE__, sql.c_str());
        return false;
    }

    // 执行SQL语句
    if (mysql_query(conn_, sql.c_str())) {
        // 打印日志信息
        LOG_ERROR("%s:%d %s execute failed", __FILE__, __LINE__, sql.c_str());
        LOG_ERROR(mysql_error(conn_));

        // 判断是否需要重连
        unsigned int err_no = mysql_errno(conn_);
        if (err_no == CR_SERVER_GONE_ERROR || err_no == CR_SERVER_LOST) {
            // 打印日志信息
            LOG_ERROR("Detected lost connection (err=%u) during execute sql, try to reconnect", err_no);
            // 尝试重连（更新操作不一定是幂等操作，比如INSERT，因此重连成功后不重试执行SQL语句）
            reconnect();
        }

        return false;
    }

    return true;
}

// 执行查询操作（select）
MYSQL_RES* MySqlConnection::query(const std::string& sql) {
    LOG_DEBUG("Execute sql: %s", sql.c_str());

    // 查询逻辑（将 mysql_query + mysql_store_result 视为一个整体，同时在内部捕获错误码，避免外部依赖 MySQL 内部状态）
    auto try_query = [&](unsigned int& err_no) -> MYSQL_RES* {
        // 执行SQL语句
        if (mysql_query(conn_, sql.c_str()) != 0) {
            err_no = mysql_errno(conn_);
            LOG_ERROR("%s:%d %s execute failed", __FILE__, __LINE__, sql.c_str());
            LOG_ERROR(mysql_error(conn_));
            return nullptr;
        }

        // 获取结果集
        MYSQL_RES* res = mysql_store_result(conn_);
        if (!res) {
            // 执行 mysql_store_result 也可能失败（例如网络中断）
            err_no = mysql_errno(conn_);
            LOG_ERROR("%s:%d %s store result failed", __FILE__, __LINE__, sql.c_str());
            LOG_ERROR(mysql_error(conn_));
            return nullptr;
        }

        return res;
    };

    // 判断连接是否有效，无效则自动重连
    if (!conn_ && !reconnect()) {
        LOG_ERROR("%s:%d %s execute failed, connection invalid", __FILE__, __LINE__, sql.c_str());
        return nullptr;
    }

    // 执行查询操作
    unsigned int err_no = 0;
    MYSQL_RES* res = try_query(err_no);
    if (res) {
        return res;
    }

    // 查询操作执行失败后，判断是否需要重连
    if (err_no == CR_SERVER_GONE_ERROR || err_no == CR_SERVER_LOST) {
        // 打印日志信息
        LOG_ERROR("Detected lost connection (err=%u) during execute sql, try to reconnect", err_no);
        // 尝试重连
        if (reconnect()) {
            // 重连成功后，再次执行查询操作（SELECT 为幂等操作）
            err_no = 0;
            res = try_query(err_no);
            if (res) {
                return res;
            }

            // 打印日志信息
            LOG_ERROR("Retry execute sql failed, err=%u", err_no);
        }
    }

    return nullptr;
}

// 发送Ping指令
bool MySqlConnection::ping() const {
    // 调用结果：0 → 成功（连接可用），非 0 → 失败（连接断开或异常）
    bool succeeded = mysql_ping(conn_) == 0;

    // 打印日志信息
    if (!succeeded) {
        LOG_ERROR("Connection ping failed");
        LOG_ERROR(mysql_error(conn_));
    }

    return succeeded;
}

// 为连接发送心跳
bool MySqlConnection::sendHeartbeat() {
    // 判断连接是否有效
    if (conn_ == nullptr) {
        // 尝试重连
        bool connected = reconnect();

        // 打印日志信息
        if (connected) {
            LOG_DEBUG("Connection send heartbeat succeeded");
        } else {
            LOG_ERROR("Connection send heartbeat failed");
        }

        return connected;
    }

    // 发送Ping指令
    if (this->ping()) {
        LOG_DEBUG("Connection send heartbeat succeeded");
        return true;
    }

    // 打印日志信息
    LOG_ERROR("Connection send heartbeat failed");

    // 尝试重连
    bool connected = reconnect();

    return connected;
}

// 重新建立连接
bool MySqlConnection::reconnect() {
    try {
        // 获取全局配置信息
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();
        const int maxReconnect = config.mysql.connectionPoolMaxReconnect;
        const int reconnectIntervalTime = config.mysql.connectionPoolReconnectIntervalTime;

        // 判断是否允许重连
        if (maxReconnect <= 0) {
            // 标记连接已损坏
            brokened_ = true;
            return false;
        }

        // 关闭原有连接（如果存在）
        if (conn_ != nullptr) {
            mysql_close(conn_);
            conn_ = nullptr;
        }

        // 初始化连接
        conn_ = mysql_init(nullptr);
        if (conn_ == nullptr) {
            // 标记连接已损坏
            brokened_ = true;
            // 打印日志信息
            LOG_ERROR("Failed to init connection during reconnect");
            return false;
        }

        // 尝试重新建立连接
        for (int i = 0; i < maxReconnect; ++i) {
            // 建立连接
            MYSQL* p = mysql_real_connect(conn_, ip_.c_str(), username_.c_str(), password_.c_str(), dbname_.c_str(),
                                          port_, nullptr, 0);

            // 判断连接是否有效
            if (p != nullptr) {
                // 标记连接没损坏
                brokened_ = false;
                // 打印日志信息
                LOG_DEBUG("Connection reconnect succeeded");
                // 设置字符集编码
                if (mysql_set_character_set(conn_, "utf8mb4") != 0) {
                    LOG_ERROR("Set charset failed after connection reconnect: %s", mysql_error(conn_));
                }
                return true;
            }

            // 打印日志信息
            LOG_ERROR("Connection reconnect failed: %d / %d. Error: %s", i + 1, maxReconnect, mysql_error(conn_));

            // 重连的时间间隔
            if (i + 1 < maxReconnect) {
                std::this_thread::sleep_for(std::chrono::milliseconds(reconnectIntervalTime * (i + 1)));
            }
        }
    } catch (const std::exception& e) {
        LOG_ERROR("Connection reconnect failed, exception: %s", e.what());
    } catch (...) {
        LOG_ERROR("Connection reconnect failed, unknown exception");
    }

    // 如果重连失败，必须确保连接指针已释放
    if (conn_ != nullptr) {
        mysql_close(conn_);
        conn_ = nullptr;
    }

    // 标记连接已损坏
    brokened_ = true;

    return false;
}

// 判断连接是否已损坏
bool MySqlConnection::isBrokened() const {
    return brokened_;
}

// 设置连接是否已损坏
void MySqlConnection::setBrokened(bool broken) {
    brokened_ = broken;
}

// 刷新连接上次使用的时间戳
void MySqlConnection::refreshLastUsedTime() {
    auto now = std::chrono::steady_clock::now();
    long long now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    lastUsedTime_.store(now_ms, std::memory_order_relaxed);
}

// 获取连接上次使用距今的时间间隔（毫秒）
long long MySqlConnection::getLastUsedIntervalTime() const {
    auto now = std::chrono::steady_clock::now();
    long long now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return now_ms - lastUsedTime_.load(std::memory_order_relaxed);
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
    return now_ms - idleStartTime_.load(std::memory_order_relaxed);
}

// 刷新连接上次发送心跳的时间戳
void MySqlConnection::refreshLastHeartbeatTime() {
    auto now = std::chrono::steady_clock::now();
    long long now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    lastHeartbeatTime_.store(now_ms, std::memory_order_relaxed);
}

// 获取连接上次发送心跳距今的时间间隔（毫秒）
long long MySqlConnection::getLastHeartbeatIntervalTime() const {
    auto now = std::chrono::steady_clock::now();
    long long now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return now_ms - lastHeartbeatTime_.load(std::memory_order_relaxed);
}