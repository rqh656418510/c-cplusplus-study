#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <atomic>
#include "public.h"
#include "MysqlConnection.h"

using namespace std;

/**
 * 连接池的实现
 */
class ConnectionPool {

public:
    // 获取单例
    ConnectionPool *getInstance();

    // 析构函数
    ~ConnectionPool();

private:
    // 构造函数私有化
    ConnectionPool();

    // 拷贝造函数私有化
    ConnectionPool(const ConnectionPool &pool);

    // 加载配置文件
    bool loadConfigFile();

    // 单例对象
    static ConnectionPool *INSTANCE;

    string _host;             // MySQL 连接地址
    string _username;         // MySQL 用户名
    string _password;         // MySQL 密码
    string _dbname;           // MySQL 数据库

    int _initSize;            // 初始连接数
    int _maxSize;             // 最大连接数
    long _maxIdleTime;        // 最大空闲时间（单位秒）
    long _connectionTimeout;  // 连接超时时间（单位毫秒）

    queue<MysqlConnection *> _connectionQueue;   // 存储 MySQL 连接的队列
    mutex _queueMutex;                           // 维护 MySQL 连接队列的线程安全互斥锁
    atomic_int _connectionCount;                 // MySQL 连接的总数量
};
