/**
 * 基于 MyMuduo 网络库开发 TCP 客户端程序
 */

#pragma once

#include <iostream>

#include "TcpClient.h"

// 聊天客户端
class ChatClient {
public:
    // 构造函数
    ChatClient(EventLoop* loop, const InetAddress& serverAddr, const std::string& nameArg);

    // 析构函数
    ~ChatClient();

    // 连接服务器
    void connect();

private:
    // 客户端绑定连接回调函数，当连接或者断开服务器时调用
    void onConnection(const TcpConnectionPtr& conn);

    // 客户端绑定消息回调函数，当有数据接收时调用
    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);

    // TCP 客户端
    TcpClient client_;

    // EventLoop 事件循环
    EventLoop* loop_;
};
