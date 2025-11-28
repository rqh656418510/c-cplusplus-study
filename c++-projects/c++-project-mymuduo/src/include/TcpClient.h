#pragma once

#include <atomic>
#include <mutex>

#include "EventLoop.h"
#include "TcpConnection.h"
#include "noncopyable.h"

// 类前置声明
class Connector;

// TCP 连接器智能指针类型定义
using ConnectorPtr = std::shared_ptr<Connector>;

// TCP 客户端
class TcpClient : noncopyable {
public:
    // 构造函数
    TcpClient(EventLoop* loop, const InetAddress& serverAddr, const std::string& nameArg);

    // 析构函数
    ~TcpClient();

    // 发起连接
    void connect();

    // 断开连接
    void disconnect();

    // 关闭客户端
    void stop();

    // 获取当前的 TCP 连接
    TcpConnectionPtr connection();

    // 获取事件循环
    EventLoop* getLoop() const;

    // 是否允许重试连接
    bool retry() const;

    // 允许重试连接
    void enableRetry();

    // 获取客户端名称
    const std::string& name() const;

    // 设置连接建立/关闭时的回调操作
    void setConnectionCallback(ConnectionCallback cb);

    // 设置有数据到来时的回调操作
    void setMessageCallback(MessageCallback cb);

    // 设置数据发送完成时的回调操作
    void setWriteCompleteCallback(WriteCompleteCallback cb);

private:
    // 创建新连接
    void newConnection(int sockfd);

    // 移除连接
    void removeConnection(const TcpConnectionPtr& conn);

    EventLoop* loop_;                              // 事件循环
    ConnectorPtr connector_;                       // 连接器
    const std::string name_;                       // 客户端名称
    ConnectionCallback connectionCallback_;        // 连接建立/关闭时的回调操作
    MessageCallback messageCallback_;              // 有数据到来时的回调操作
    WriteCompleteCallback writeCompleteCallback_;  // 数据发送完成时的回调操作
    std::atomic_bool retry_;                       // 是否允许重试连接（即断线重连）
    std::atomic_bool connect_;                     // 是否需要连接
    int nextConnId_;                               // 下一个 TCP 连接的 ID
    std::mutex mutex_;                             // 互斥锁
    TcpConnectionPtr connection_;                  // TCP 连接
};