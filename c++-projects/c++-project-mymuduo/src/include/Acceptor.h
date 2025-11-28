#pragma once

#include <functional>

#include "Channel.h"
#include "Socket.h"
#include "noncopyable.h"

// 类前置声明
class EventLoop;
class InetAddress;

// TCP 连接接受器类
class Acceptor : noncopyable {
public:
    // 有新连接到来时的回调操作类型定义
    using NewConnectionCallback = std::function<void(int sockFd, const InetAddress&)>;

    // 构造函数
    Acceptor(EventLoop* loop, const InetAddress& listenAddr, bool reuseport);

    // 析构函数
    ~Acceptor();

    // 设置有新连接到来时的回调操作
    void setNewConnectionCallback(const NewConnectionCallback& cb);

    // 监听连接请求（即监听有新的客户端连接进来）
    void listen();

    // 获取是否正在监听连接请求
    bool listenning() const;

private:
    // 处理读事件（即处理有新客户端连接进来）
    void handleRead();

    EventLoop* loop_;        // Acceptor 使用的就是用户自定义的那个 baseLoop，也称作 mainLoop
    Socket acceptSocket_;    // 用于监听的 socket
    Channel acceptChannel_;  // 用于监听 acceptSocket_ 上的可读事件（即有新连接到来）
    NewConnectionCallback newConnectionCallback_;  // 有新连接到来时的回调操作
    bool listenning_;                              // 标记是否正在监听连接请求
};