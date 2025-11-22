#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "noncopyable.h"

// 类前置声明
class EventLoop;
class EventLoopThread;

// 事件循环线程池类
class EventLoopThreadPool : noncopyable {
public:
    // 线程初始化回调操作的类型定义
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    // 构造函数
    EventLoopThreadPool(EventLoop* baseLoop, const std::string& nameArg);

    // 析构函数
    ~EventLoopThreadPool();

    // 设置线程池的线程数量
    void setThreadNum(int numThreads);

    // 启动线程池
    void start(const ThreadInitCallback& cb = ThreadInitCallback());

    // 获取下一个被选中的事件循环（如果工作在多线程中，baseLoop 默认以轮询的方式分配 Channel 给 subLoop）
    EventLoop* getNextLoop();

    // 返回所有事件循环
    std::vector<EventLoop*> getAllLoops();

    // 返回线程池是否已启动
    bool started() const;

    // 返回线程池的名称
    const std::string& name() const;

private:
    EventLoop* baseLoop_;  // 基础事件循环（通常是主线程上的事件循环）
    std::string name_;     // 线程池名称
    bool started_;         // 标记线程池是否已启动
    int numThreads_;       // 线程数量
    int next_;             // 下一个被选中的事件循环的索引
    std::vector<std::unique_ptr<EventLoopThread>> threads_;  // 事件循环线程对象的集合
    std::vector<EventLoop*> loops_;                          // 事件循环对象的集合
};