#ifndef CONFIG_H
#define CONFIG_H

/**
 * 全局配置信息的头文件
 */

#include <iostream>
#include <string>

// MySQL 连接信息
static const int DB_PORT = 3306;
static const std::string DB_IP = "127.0.0.1";
static const std::string DB_USER = "root";
static const std::string DB_PASSWORD = "Cxx_Chat_12345";
static const std::string DB_NAME = "chat";

#endif  // CONFIG_H
