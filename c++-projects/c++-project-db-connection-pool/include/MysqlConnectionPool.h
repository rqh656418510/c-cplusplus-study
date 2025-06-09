/**
 * MySQL 连接池的定义
 */

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

// MySQL 连接池类
class MysqlConnectionPool {

public:
    // 析构函数
    ~MysqlConnectionPool();

    // 关闭连接池
    void close();

    // 判断连接池是否已关闭
    bool isClosed() const;

    // 获取连接池中的连接数量
    int getSize() const;

    // 获取连接池单例
    static MysqlConnectionPool *getInstance();

    // 获取 MySQL 连接
    shared_ptr<MysqlConnection> getConnection();

private:
    // 私有化构造函数
    MysqlConnectionPool();

    // 删除拷贝构造函数
    MysqlConnectionPool(const MysqlConnectionPool &) = delete;

    // 删除赋值运算符
    MysqlConnectionPool &operator=(const MysqlConnectionPool &) = delete;

    // 加载配置文件
    bool loadConfigFile();

    // 生产 MySQL 连接
    void produceConnection();

    // 扫描多余的空闲连接，并释放连接
    void scanIdleConnection();

    // 单例对象
    static MysqlConnectionPool *INSTANCE;

    string _host;             // MySQL 连接地址
    string _username;         // MySQL 用户名
    string _password;         // MySQL 密码
    string _dbname;           // MySQL 数据库

    int _initSize;            // 初始连接数
    int _maxSize;             // 最大连接数
    int _maxIdleTime;         // 最大空闲时间（单位秒）
    int _connectionTimeout;   // 连接超时时间（单位毫秒）

    atomic_int _connectionCount;                 // MySQL 连接的总数量
    queue<MysqlConnection *> _connectionQueue;   // 存储 MySQL 连接的队列
    mutex _queueMutex;                           // 维护 MySQL 连接队列线程安全的互斥锁
    condition_variable _cv;                      // 条件变量，用于连接生产者线程和连接消费者线程之间的通信
    atomic_bool _closed;                         // 连接池是否已关闭
};
