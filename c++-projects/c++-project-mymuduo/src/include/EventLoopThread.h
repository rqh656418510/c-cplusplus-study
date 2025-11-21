#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>

#include "Thread.h"
#include "noncopyable.h"

class EventLoop;

// 事件循环线程类
class EventLoopThread : noncopyable {
public:
    // 线程初始化回调操作的类型定义
    using ThreadInitCallback = std::function<void(EventLoop *)>;

    // 构造函数
    EventLoopThread(const ThreadInitCallback &cb = ThreadInitCallback(), const std::string &name = std::string());

    // 析构函数
    ~EventLoopThread();

    // 启动线程
    EventLoop *startLoop();

private:
    // 线程执行函数
    void threadFunc();

    EventLoop *loop_;               // 事件循环
    bool exiting_;                  // 标记线程是否正在退出
    Thread thread_;                 // 线程对象（EventLoop 所在的线程）
    std::mutex mutex_;              // 互斥锁
    std::condition_variable cond_;  // 条件变量
    ThreadInitCallback callback_;   // 线程初始化回调操作
};