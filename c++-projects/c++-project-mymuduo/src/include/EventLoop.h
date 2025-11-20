#pragma once

#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

#include "Timestamp.h"
#include "noncopyable.h"

// 类前置声明
class Channel;
class Poller;

// 事件循环类
class EventLoop : noncopyable {
public:
    using Functor = std::function<void()>;

    // 构造函数
    EventLoop();

    // 析构函数
    ~EventLoop();

    // 开启事件循环
    void loop();

    // 退出事件循环
    void quit();

    // 获取 Poller 返回发生事件的时间点
    Timestamp pollReturnTime() const;

    // 在当前 EventLoop 所在线程执行回调操作
    void runInLoop(Functor cb);

    // 将回调操作添加到队列中，唤醒 EventLoop 所在线程执行回调操作
    void queueInLoop(Functor cb);

    // 唤醒 EventLoop 所在线程
    void wakeup();

    // 更新 Channel
    void updateChannel(Channel* channel);

    // 移除 Channel
    void removeChannel(Channel* channel);

    // 判断 EventLoop 中是否存在某个 Channel
    bool hasChannel(Channel* channel);

    // 判断当前线程是否是 EventLoop 所在线程
    bool isInLoopThread() const;

private:
    // 处理 Wakeup Channel 的读事件
    void handleRead();

    // 执行所有回调操作
    void doPendingFunctors();

    // Channel 列表的类型定义
    using ChannelList = std::vector<Channel*>;

    std::atomic_bool looping_;  // 事件循环状态
    std::atomic_bool quit_;     // 标识退出 EventLoop 循环

    const pid_t threadId_;            // 记录当前 EventLoop 所在线程的 ID
    Timestamp pollReturnTime_;        // 记录 Poller 返回发生事件的时间点
    std::unique_ptr<Poller> poller_;  // EventLoop 使用的 Poller（I/O 多路复用器）

    int wakeupFd_;                            // 用于唤醒 EventLoop 所在线程的 fd（非常重要）
    std::unique_ptr<Channel> wakeupChannel_;  // 用于唤醒 EventLoop 所在线程的 Channel（非常重要）

    ChannelList activeChannels_;  // 保存 Poller 返回的活跃的 Channel 列表

    std::atomic_bool callingPendingFunctors_;  // 标识当前 EventLoop 是否有需要执行的回调操作
    std::vector<Functor> pendingFunctors_;     // 保存当前 EventLoop 需要执行的所有回调操作
    std::mutex mutex_;                         // 保护 pendingFunctors_ 容器线程安全的互斥锁
};
