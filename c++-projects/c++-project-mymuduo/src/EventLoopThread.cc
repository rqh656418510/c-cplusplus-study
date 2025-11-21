#include "EventLoopThread.h"

#include <EventLoop.h>

#include <memory>

// 构造函数
EventLoopThread::EventLoopThread(const ThreadInitCallback &cb, const std::string &name)
    : loop_(nullptr),
      exiting_(false),
      thread_(std::bind(&EventLoopThread::threadFunc, this), name),
      mutex_(),
      cond_(),
      callback_(cb) {
}

// 析构函数
EventLoopThread::~EventLoopThread() {
    // 标记线程正在退出
    exiting_ = true;

    if (loop_ != nullptr) {
        // 退出线程循环
        loop_->quit();
        // 等待线程执行结束
        thread_.join();
    }
}

// 在对应的线程中启动事件循环
EventLoop *EventLoopThread::startLoop() {
    // 启动底层新创建的线程
    thread_.start();

    EventLoop *loop = nullptr;
    {
        // 等待线程函数 threadFunc() 创建好事件循环对象
        std::unique_lock<std::mutex> lock(mutex_);
        while (loop_ == nullptr) {
            cond_.wait(lock);
        }
        loop = loop_;
    }

    return loop;
}

// 线程执行函数
void EventLoopThread::threadFunc() {
    // 新创建一个独立的事件循环，和上面底层新创建的线程一一对应
    EventLoop loop;

    // 执行线程初始化回调操作
    if (callback_) {
        callback_(&loop);
    }

    {
        // 将新创建的事件循环对象赋值给成员变量 loop_，需要保证线程安全
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = &loop;

        // 通知 startLoop() 成员函数，成员变量 loop_ 已经赋值完毕
        cond_.notify_one();
    }

    // 开启事件循环
    loop.loop();

    // 事件循环退出后，重置成员变量 loop_
    std::unique_lock<std::mutex> lock(mutex_);
    loop_ = nullptr;
}