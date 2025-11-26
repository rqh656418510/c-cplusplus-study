#pragma once

#include <functional>
#include <iostream>
#include <memory>

#include "Timestamp.h"
#include "noncopyable.h"

// 类前置声明
class EventLoop;

/**
 * Channel 可以理解为通道，封装了 socket fd 和其感兴趣的 event（事件），比如 EPOLLIN、EPOLLOUT 事件，还绑定了 Poller
 * 返回的具体事件
 */
class Channel : noncopyable {
public:
    // 事件回调函数类型定义
    using EventCallback = std::function<void()>;

    // 读事件的回调函数类型定义
    using ReadEventCallback = std::function<void(Timestamp)>;

    // 构造函数
    Channel(EventLoop* loop, int fd);

    // 析构函数
    ~Channel();

    // fd 得到 poller 通知以后，处理事件的函数
    void handleEvent(Timestamp receiveTime);

    /********** 设置事件的回调操作 **********/

    void setReadCallback(ReadEventCallback cb) {
        readCallback_ = std::move(cb);
    }

    void setWriteCallback(EventCallback cb) {
        writeCallback_ = std::move(cb);
    }

    void setCloseCallback(EventCallback cb) {
        closeCallback_ = std::move(cb);
    }

    void setErrorCallback(EventCallback cb) {
        errorCallback_ = std::move(cb);
    }

    /********** 获取和设置 fd 和 events **********/

    // 获取 socket 的 fd
    int fd() const {
        return fd_;
    }

    // 获取 fd 感兴趣的事件
    int events() {
        return events_;
    }

    // 设置 fd 上发生的具体事件
    void set_revents(int revent) {
        revents_ = revent;
    }

    /********** 设置 fd 相应的事件状态 **********/

    // 开启监听 fd 上的读事件
    void enableReading() {
        events_ |= kReadEvent;
        update();
    }

    // 关闭监听 fd 上的读事件
    void disableReading() {
        events_ &= ~kReadEvent;
        update();
    }

    // 开启监听 fd 上的写事件
    void enableWriting() {
        events_ |= kWriteEvent;
        update();
    }

    // 关闭监听 fd 上的写事件
    void disableWriting() {
        events_ &= ~kWriteEvent;
        update();
    }

    // 禁止监听 fd 上的所有事件（读 + 写）
    void disableAll() {
        events_ = kNoneEvent;
        update();
    }

    /********** 获取 fd 当前的事件状态 **********/

    // 判断当前是否没有监听任何事件（既不读也不写）
    bool isNoneEvent() const {
        return events_ == kNoneEvent;
    }

    // 判断当前是否正在监听写事件
    bool isWriting() const {
        return events_ & kWriteEvent;
    }

    // 判断当前是否正在监听读事件
    bool isReading() const {
        return events_ & kReadEvent;
    }

    // 返回当前 Channel 在 Poller 中的状态
    int index() {
        return index_;
    }

    // 设置当前 Channel 在 Poller 中的状态
    void set_index(int index) {
        index_ = index;
    }

    // 防止当 Channel 被手动 remove 掉后，Channel 还在执行事件的回调操作
    void tie(const std::shared_ptr<void>& obj);

    // 从 Poller 中删除当前 Channel
    void remove();

private:
    // 更新 Channel 状态到 Poller 中
    void update();

    // 处理事件，有了 guard 之后，Channel 就不会在被手动 remove 掉后还继续执行事件的回调操作
    void handleEventWithGuard(Timestamp receiveTime);

    // 定义 Channel 支持的事件类型
    static const int kNoneEvent;   // 无事件
    static const int kReadEvent;   // 读事件
    static const int kWriteEvent;  // 写事件

    EventLoop* loop_;  // Channel 所属的事件循环
    const int fd_;     // fd，是 Poller 监听的对象
    int events_;       // 注册 fd 上感兴趣的事件
    int revents_;      // poller 返回的 fd 上具体发生的事件
    int index_;        // 标记 Channel 在 Poller 中的状态

    std::weak_ptr<void> tie_;  // 用于防止 Channel 被手动 remove 掉后，Channel 还在执行事件的回调操作
    bool tied_;                // 标记是否已绑定 tie_

    // Channel 里面能够获知 fd 上最终发生的具体事件（revents_），所以由它负责调用具体事件的回调操作（即事件分发）
    ReadEventCallback readCallback_;  // 读事件的回调函数
    EventCallback writeCallback_;     // 写事件的回调函数
    EventCallback closeCallback_;     // 关闭事件的回调函数
    EventCallback errorCallback_;     // 错误事件的回调函数
};