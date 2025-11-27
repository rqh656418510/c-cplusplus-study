#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "Acceptor.h"
#include "Callbacks.h"
#include "EventLoop.h"
#include "EventLoopThreadPool.h"
#include "InetAddress.h"
#include "atomic"
#include "noncopyable.h"
#include "unordered_map"

// TCP 服务器类
class TcpServer : noncopyable {
public:
    // 线程初始化回调操作类型定义
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    // 端口复用选项枚举类型定义
    enum Option {
        kNoReusePort,
        kReusePort,
    };

    // 构造函数
    TcpServer(EventLoop* loop, const InetAddress& listenAddr, const std::string nameArg, Option option = kNoReusePort);

    // 析构函数
    ~TcpServer();

    // 获取服务器监听的 IP 和端口信息
    const std::string& ipPort() const;

    // 获取服务器名称
    const std::string& name() const;

    // 获取服务器的事件循环
    EventLoop* getLoop() const;

    // 设置线程池的线程数量（即底层 subLoop 的数量）
    void setThreadNum(int numThreads);

    // 启动服务器（线程安全）
    void start();

    // 设置线程初始化回调操作
    void setThreadInitCallback(const ThreadInitCallback& cb);

    // 设置有新连接到来时的回调操作
    void setConnectionCallback(const ConnectionCallback& cb);

    // 设置有数据到来时的回调操作
    void setMessageCallback(const MessageCallback& cb);

    // 设置数据发送完成时的回调操作
    void setWriteCompleteCallback(const WriteCompleteCallback& cb);

private:
    // TCP 连接集合类型定义
    using ConnectionMap = std::unordered_map<std::string, TcpConnectionPtr>;

    // 创建 TCP 连接（在 baseLoop 上执行）
    void newConnection(int sockfd, const InetAddress& peerAddr);

    // 移除 TCP 连接
    void removeConnection(const TcpConnectionPtr& conn);

    // 移除 TCP 连接（在 baseLoop 上执行）
    void removeConnectionInLoop(const TcpConnectionPtr& conn);

    EventLoop* loop_;           // 用户自定义的 EventLoop（即 baseLoop，也称作 mainLoop）
    const std::string ipPort_;  // 服务器监听的 IP 和端口信息
    const std::string name_;    // 服务器名称

    std::unique_ptr<Acceptor> acceptor_;  // 用于监听新连接的 Acceptor 对象，运行在 baseLoop 上
    std::shared_ptr<EventLoopThreadPool> threadPool_;  // 事件循环线程池

    ConnectionCallback connectionCallback_;        // 有新连接到来时的回调操作
    MessageCallback messageCallback_;              // 有数据到来时的回调操作
    WriteCompleteCallback writeCompleteCallback_;  // 数据发送完成时的回调操作
    ThreadInitCallback threadInitCallback_;        // 线程初始化回调操作

    std::atomic_int started_;    // 标记服务器是否已经启动
    int nextConnId_;             // 下一个 TCP 连接的 ID
    ConnectionMap connections_;  // 保存所有的 TCP 连接
};