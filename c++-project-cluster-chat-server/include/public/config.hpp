#ifndef CONFIG_H
#define CONFIG_H

/**
 * 全局配置信息的头文件
 */

#include <iostream>

using namespace std;

// MySQL 连接信息
static const string DB_IP = "127.0.0.1";
static const int DB_PORT = 3306;
static const string DB_USER = "root";
static const string DB_PASSWORD = "Cxx_Chat_12345";
static const string DB_NAME = "chat";

// Redis 连接信息
static const string REDIS_IP = "127.0.0.1";
static const int REDIS_PORT = 6379;

#endif  // CONFIG_H