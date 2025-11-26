#pragma once

#include <functional>
#include <memory>

#include "Timestamp.h"

// 类前置声明
class Buffer;
class TcpConnection;

// TCP 连接智能指针类型定义
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;

// 有新连接到来时的回调函数类型定义
using ConnectionCallback = std::function<void(const TcpConnectionPtr&)>;

// 关闭连接时的回调函数类型定义
using CloseCallback = std::function<void(const TcpConnectionPtr&)>;

// 数据发生完成时的回调函数类型定义
using WriteCompleteCallback = std::function<void(const TcpConnectionPtr&)>;

// 有消息到来时的回调函数类型定义
using MessageCallback = std::function<void(const TcpConnectionPtr&, Buffer*, Timestamp)>;

// 高水位的回调函数类型定义
using HighWaterMarkCallback = std::function<void(const TcpConnectionPtr&, size_t)>;

// 默认的回调函数
void defaultConnectionCallback(const TcpConnectionPtr& conn);
void defaultMessageCallback(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp receiveTime);
