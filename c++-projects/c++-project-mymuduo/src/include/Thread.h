#pragma once

#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>

#include "noncopyable.h"

// 线程类
class Thread : noncopyable {
public:
    // 线程执行函数的类型定义
    using ThreadFunc = std::function<void()>;

    // 构造函数
    explicit Thread(ThreadFunc func, const std::string& name = std::string());

    // 析构函数
    ~Thread();

    // 启动线程
    void start();

    // 等待线程执行结束
    void join();

    // 获取线程 ID
    pid_t tid();

    // 获取线程名称
    const std::string& name() const;

    // 获取已创建的线程数量
    static int numCreated();

private:
    // 设置线程的默认名称
    void setDefaultName();

    bool started_;                         // 标记线程是否已启动
    bool joined_;                          // 标记线程是否已经 join，防止重复 join 或析构时未 join
    std::shared_ptr<std::thread> thread_;  // 线程对象
    pid_t tid_;                            // 线程 ID
    ThreadFunc func_;                      // 线程执行函数
    std::string name_;                     // 线程名称
    static std::atomic_int numCreated_;    // 已创建的线程数量
};