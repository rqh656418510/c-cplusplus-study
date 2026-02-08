#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

#include "MySqlConnection.h"

// 声明MySQL连接的指针类型（使用unique_ptr，禁止拷贝MySQL连接，限制每个连接在同一时刻只会被一个线程使用）
using MySqlConnectionPtr = std::unique_ptr<MySqlConnection, std::function<void(MySqlConnection *)>>;

// MySQL连接池（单例对象）
class MySqlConnectionPool {
public:
    // 关闭连接池
    void close();

    // 判断连接池是否已关闭
    bool isClosed() const;

    // 获取连接池中的连接数量
    int getSize() const;

    // 获取连接池单例对象
    static MySqlConnectionPool *getInstance();

    // 从连接池中获取MySQL连接
    MySqlConnectionPtr getConnection();

private:
    // 私有构造函数
    MySqlConnectionPool();

    // 私有析构函数
    ~MySqlConnectionPool();

    // 删除拷贝构造函数
    MySqlConnectionPool(const MySqlConnectionPool &) = delete;

    // 删除赋值操作运算符
    MySqlConnectionPool &operator=(const MySqlConnectionPool &) = delete;

    // 生产MySQL连接
    void produceConnection();

    // 扫描多余的空闲连接，并释放连接
    void scanIdleConnection();

    int initSize_;           // 连接池的初始连接数
    int maxSize_;            // 连接池的最大连接数
    int maxIdleTime_;        // 连接池的最大空闲时间（单位秒）
    int connectionTimeout_;  // 从连接池获取连接的超时时间（单位毫秒）

    std::thread produceThread_;   // 生产连接的线程
    std::thread scanIdleThread_;  // 扫描空闲连接的线程

    std::atomic_int connectionCount_;                // MySQL连接池中连接的总数量
    std::queue<MySqlConnection *> connectionQueue_;  // 存储MySQL连接的队列
    std::mutex queueMutex_;                          // 维护MySQL连接队列线程安全的互斥锁
    std::condition_variable cv_;  // 条件变量，用于连接生产者线程和连接消费者线程之间的通信
    std::atomic_bool closed_;     // 连接池是否已关闭
};