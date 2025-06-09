#include "db.hpp"

#include <muduo/base/Logging.h>

#include "config.hpp"

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
    MYSQL *p = mysql_real_connect(_conn, DB_IP.c_str(), DB_USER.c_str(), DB_PASSWORD.c_str(), DB_NAME.c_str(), DB_PORT,
                                  nullptr, 0);
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