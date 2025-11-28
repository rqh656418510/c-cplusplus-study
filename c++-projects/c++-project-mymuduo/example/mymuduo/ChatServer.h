/**
 * 基于 MyMuduo 网络库开发 TCP 服务器程序
 */

#pragma once

#include <iostream>

#include "TcpServer.h"

// 聊天服务器
class ChatServer {
public:
    // 构造函数
    ChatServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg);

    // 析构函数
    ~ChatServer();

    // 启动服务器
    void start();

private:
    // 处理用户的连接创建和断开
    void onConnection(const TcpConnectionPtr &conn);

    // 服务器绑定消息回调函数，当有数据接收时调用
    void onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time);

    // TCP 服务器
    TcpServer server_;

    // EventLoop 事件循环
    EventLoop *loop_;
};