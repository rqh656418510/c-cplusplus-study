#include "mysqldb.h"

#include <iostream>

#include "config.h"

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
    // 发起连接
    MYSQL *p = mysql_real_connect(_conn, DB_IP.c_str(), DB_USER.c_str(), DB_PASSWORD.c_str(), DB_NAME.c_str(), DB_PORT,
                                  nullptr, 0);

    if (p == nullptr) {
        std::cout << "[ERROR] connect mysql failed" << std::endl;
        std::cout << "[ERROR] " << mysql_error(_conn) << std::endl;
        return false;
    }

    // C和C++代码默认的编码字符是ASCII，如果不设置，从MySQL查询到的中文内容可能会显示乱码
    if (mysql_set_character_set(_conn, "utf8mb4") != 0) {
        std::cout << "Set charset failed" << std::endl;
        std::cout << "[ERROR] " << mysql_error(_conn) << std::endl;
        return false;
    }

    std::cout << "[DEBUG] connect mysql success" << std::endl;
    return true;
}

// 更新操作
bool MySQL::update(std::string sql) {
    std::cout << "[DEBUG] " << sql << std::endl;

    if (mysql_query(_conn, sql.c_str())) {
        std::cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << " " << sql << " execute failed!" << std::endl;
        std::cout << "[ERROR] " << mysql_error(_conn) << std::endl;
        return false;
    }

    return true;
}

// 查询操作
MYSQL_RES *MySQL::query(std::string sql) {
    std::cout << "[DEBUG] " << sql << std::endl;

    if (mysql_query(_conn, sql.c_str())) {
        std::cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << " " << sql << " execute failed!" << std::endl;
        std::cout << "[ERROR] " << mysql_error(_conn) << std::endl;
        return nullptr;
    }

    return mysql_store_result(_conn);
}

// 获取数据库连接
MYSQL *MySQL::getConnection() {
    return _conn;
}
