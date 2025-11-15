/**
 * 基于 Muduo 官方网络库开发 TCP 客户端程序
 */

#pragma once

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>

#include <iostream>
#include <string>

class ChatClient {
public:
    // 构造函数
    ChatClient(muduo::net::EventLoop* loop, const muduo::net::InetAddress& serverAddr, const std::string& nameArg);

    // 析构函数
    ~ChatClient();

    // 连接服务端
    void connect();

private:
    // 客户端绑定连接回调函数，当连接或者断开服务端时调用
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    // 客户端绑定消息回调函数，当有数据接收时调用
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time);

    // TCP 客户端
    muduo::net::TcpClient _client;

    // EventLoop 事件回环
    muduo::net::EventLoop* _loop;
};
