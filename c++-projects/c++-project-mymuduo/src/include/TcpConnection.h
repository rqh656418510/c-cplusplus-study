#pragma once

#include <atomic>
#include <iostream>
#include <memory>
#include <string>

#include "Buffer.h"
#include "Callbacks.h"
#include "InetAddress.h"
#include "noncopyable.h"

// 类前置声明
class EventLoop;
class Channel;
class Socket;

// TCP 连接类
class TcpConnection : noncopyable, public std::enable_shared_from_this<TcpConnection> {
public:
    // 构造函数
    TcpConnection(EventLoop* loop, const std::string& nameArg, int sockfd, const InetAddress& localAddr,
                  const InetAddress& peerAddr);

    // 析构函数
    ~TcpConnection();

    // 获取 TCP 连接所在的事件循环
    EventLoop* getLoop() const;

    // 获取 TCP 连接的名称
    const std::string& name() const;

    // 获取 TCP 连接的本地网络地址
    const InetAddress& localAddress() const;

    // 获取 TCP 连接的远程网络地址
    const InetAddress& peerAddress() const;

    // 判断 TCP 连接是否处于已连接状态
    bool connected() const;

    // 判断 TCP 连接是否处于断开状态
    bool disconnected() const;

    // 发送数据
    void send(const void* message, int len);

    // 关闭 TCP 连接
    void shutdown();

    // 设置连接建立/关闭时的回调操作
    void setConnectionCallback(const ConnectionCallback& cb);

    // 设置有数据到来时的回调操作
    void setMessageCallback(const MessageCallback& cb);

    // 设置数据发送完成时的回调操作
    void setWriteCompleteCallback(const WriteCompleteCallback& cb);

    // 设置高水位时的回调操作
    void setHighWaterMarkCallback(const HighWaterMarkCallback& cb, size_t highWaterMark);

    // 设置连接关闭时的回调操作
    void setCloseCallback(const CloseCallback& cb);

    // 获取输入缓冲区
    Buffer* inputBuffer();

    // 获取输出缓冲区
    Buffer* outBuffer();

    // 连接建立
    void connectEstablished();

    // 连接销毁
    void connectDestroyed();

private:
    // TCP 连接的状态
    enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };

    // 处理读事件
    void handleRead(Timestamp receiveTime);

    // 处理写事件
    void handleWrite();

    // 处理关闭事件
    void handleClose();

    // 处理错误事件
    void handleError();

    // 在事件循环（EventLoop）中发送数据
    void sendInLoop(const void* message, size_t len);

    // 在事件循环（EventLoop）中关闭 TCP 连接
    void shutdownInLoop();

    // 设置 TCP 连接的状态
    void setState(StateE state);

    // 将 TCP 连接的状态转换为字符串
    const char* stateToString() const;

    EventLoop* loop_;         // TCP 连接所在的事件循环，TCP 连接运行在 subLoop 中
    const std::string name_;  // TCP 连接的名称
    std::atomic_int state_;   // TCP 连接的状态
    bool reading_;            // 标记是否正在读数据

    std::unique_ptr<Socket> socket_;    // TCP 连接对应的套接字对象
    std::unique_ptr<Channel> channel_;  // TCP 连接对应的管道对象

    const InetAddress localAddr_;  // TCP 连接的本地网络地址
    const InetAddress peerAddr_;   // TCP 连接的远程网络地址

    ConnectionCallback connectionCallback_;        // 连接建立/关闭时的回调操作
    MessageCallback messageCallback_;              // 有数据到来时的回调操作
    WriteCompleteCallback writeCompleteCallback_;  // 数据发送完成时的回调操作
    HighWaterMarkCallback highWaterMarkCallback_;  // 高水位时的回调操作
    CloseCallback closeCallback_;                  // 连接关闭时的回调操作

    size_t highWaterMark_;  // 高水位的大小（默认 64M）
    Buffer inputBuffer_;    // 输入缓冲区
    Buffer outputBuffer_;   // 输出缓冲区
};