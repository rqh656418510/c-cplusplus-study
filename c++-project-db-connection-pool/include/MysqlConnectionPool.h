#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <atomic>
#include <thread>
#include <memory>
#include <functional>
#include <condition_variable>
#include "public.h"
#include "MysqlConnection.h"

using namespace std;

/**
 * MySQL 连接池的实现
 */
class MysqlConnectionPool {

public:
    // 获取单例
    MysqlConnectionPool *getInstance();

    // 析构函数
    ~MysqlConnectionPool();

    // 获取 MySQL 连接
    shared_ptr<MysqlConnection> *getConnection();

private:
    // 构造函数私有化
    MysqlConnectionPool();

    // 拷贝造函数私有化
    MysqlConnectionPool(const MysqlConnectionPool &pool);

    // 加载配置文件
    bool loadConfigFile();

    // 生产 MySQL 连接
    void produceConnection();

    // 单例对象
    static MysqlConnectionPool *INSTANCE;

    string _host;             // MySQL 连接地址
    string _username;         // MySQL 用户名
    string _password;         // MySQL 密码
    string _dbname;           // MySQL 数据库

    int _initSize;            // 初始连接数
    int _maxSize;             // 最大连接数
    long _maxIdleTime;        // 最大空闲时间（单位秒）
    long _connectionTimeout;  // 连接超时时间（单位毫秒）

    atomic_int _connectionCount;                 // MySQL 连接的总数量
    queue<MysqlConnection *> _connectionQueue;   // 存储 MySQL 连接的队列
    mutex _queueMutex;                           // 维护 MySQL 连接队列线程安全的互斥锁
    condition_variable _cv;                      // 设置条件变量，用于连接生产者线程和连接消费者线程的通信
};
