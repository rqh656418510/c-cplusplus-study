/**
 * 基于 MyMuduo 网络库开发 TCP 服务端程序
 */

#pragma once

#include <iostream>
#include <string>

#include "TcpServer.h"
#include "Timestamp.h"

class EchoServer {
public:
    // 构造函数
    EchoServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg);

    // 析构函数
    ~EchoServer();

    // 启动服务端
    void start();

private:
    // 处理用户的连接创建和断开
    void onConnection(const TcpConnectionPtr &conn);

    // 处理用户读写事件（比如接收客户端发送的数据）
    void onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time);

    // TCP 服务端
    TcpServer server_;

    // EventLoop 事件循环
    EventLoop *loop_;
};