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
    using EventCallback = std::function<void()>;
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

    int fd() const {
        return fd_;
    }

    int events() {
        return events_;
    }

    void set_revents(int revent) {
        revents_ = revent;
    }

    /********** 设置 fd 相应的事件状态 **********/

    void enableReading() {
        events_ |= kReadEvent;
        update();
    }

    void disableReading() {
        events_ &= ~kReadEvent;
        update();
    }

    void enableWriting() {
        events_ |= kWriteEvent;
        update();
    }

    void disableWriting() {
        events_ &= ~kWriteEvent;
        update();
    }

    void disableAll() {
        events_ = kNoneEvent;
        update();
    }

    /********** 获取 fd 当前的事件状态 **********/

    bool isNoneEvent() const {
        return events_ == kNoneEvent;
    }

    bool isWriting() const {
        return events_ & kWriteEvent;
    }

    bool isReading() const {
        return events_ & kReadEvent;
    }

    int index() {
        return index_;
    }

    void set_index(int index) {
        index_ = index;
    }

    // 防止当 Channel 被手动 remove 掉后，Channel 还在执行事件的回调操作
    void tie(const std::shared_ptr<void>& obj);

    // 从 Poller 中删除自己
    void remove();

private:
    // 更新 Channel 状态到 Poller 中
    void update();

    // 处理事件，有了 guard 之后，Channel 就不会在被手动 remove 掉后还继续执行事件的回调操作了
    void handleEventWithGuard(Timestamp receiveTime);

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop* loop_;  // 事件循环
    const int fd_;     // fd，Poller 监听的对象
    int events_;       // 注册 fd 感兴趣的事件
    int revents_;      // poller 返回的具体发生的事件
    int index_;

    std::weak_ptr<void> tie_;  // 用于防止 channel 被手动 remove 掉后，channel 还在执行事件的回调操作
    bool tied_;                // 标记是否已绑定

    // Channel 里面能够获知 fd 最终发生的具体事件（revents_），所以它负责调用具体事件的回调操作（即事件分发）
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};
