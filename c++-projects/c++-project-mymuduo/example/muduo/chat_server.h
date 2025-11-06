/**
 * 基于 Muduo 官方网络库开发 TCP 服务端程序
 */

#pragma once

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <functional>
#include <iostream>
#include <string>

class ChatServer {
public:
    // 构造函数
    ChatServer(muduo::net::EventLoop *loop, const muduo::net::InetAddress &listenAddr, const std::string &nameArg);

    // 析构函数
    ~ChatServer();

    // 启动服务端
    void start();

private:
    // 处理用户的连接创建和断开
    void onConnection(const muduo::net::TcpConnectionPtr &conn);

    // 处理用户读写事件（比如接收客户端发送的数据）
    void onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buffer, muduo::Timestamp time);

    // TCP 服务端
    muduo::net::TcpServer _server;

    // EventLoop 事件回环
    muduo::net::EventLoop *_loop;
};
