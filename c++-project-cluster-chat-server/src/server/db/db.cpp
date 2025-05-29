#include "db.h"

#include <muduo/base/Logging.h>

// 数据库配置信息
static string server = "127.0.0.1";
static string user = "root";
static string password = "Cxx_Chat_12345";
static string dbname = "chat";

// 初始化数据库连接
MySQL::MySQL() {
    _conn = mysql_init(nullptr);
}

// 释放数据库连接
MySQL::~MySQL() {
    if (_conn != nullptr) {
        mysql_close(_conn);
    }
}

// 连接数据库
bool MySQL::connect() {
    MYSQL *p =
        mysql_real_connect(_conn, server.c_str(), user.c_str(), password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr) {
        // C和C++代码默认的编码字符是ASCII，如果不设置，从MySQL查询到的中文内容可能会显示？乱码
        mysql_query(_conn, "set names utf8mb4");
        LOG_INFO << "connect mysql success!";
    } else {
        LOG_ERROR << "connect mysql failed!";
        LOG_ERROR << mysql_error(_conn);
    }

    return p;
}

// 更新操作
bool MySQL::update(string sql) {
    LOG_DEBUG << sql;
    if (mysql_query(_conn, sql.c_str())) {
        LOG_ERROR << __FILE__ << ":" << __LINE__ << " " << sql << " execute failed!";
        LOG_ERROR << mysql_error(_conn);
        return false;
    }

    return true;
}

// 查询操作
MYSQL_RES *MySQL::query(string sql) {
    LOG_DEBUG << sql;
    if (mysql_query(_conn, sql.c_str())) {
        LOG_ERROR << __FILE__ << ":" << __LINE__ << " " << sql << " execute failed!";
        LOG_ERROR << mysql_error(_conn);
        return nullptr;
    }

    return mysql_store_result(_conn);
}

// 获取数据库连接
MYSQL *MySQL::getConnection() {
    return _conn;
}