#pragma once

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <functional>
#include <iostream>
#include <string>

// 基于Muduo开发服务端程序
class ChatServer {
public:
    // 构造函数
    ChatServer(muduo::net::EventLoop *loop, const muduo::net::InetAddress &listenAddr, const std::string &nameArg)
        : _server(loop, listenAddr, nameArg), _loop(loop) {
        // 设置服务端注册用户连接的创建和断开回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));

        // 设置服务端注册用户读写事件的回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2,
                                             std::placeholders::_3));

        // 设置EventLoop的线程数量（比如：1个I/O线程，3个Worker线程）
        _server.setThreadNum(4);
    }

    // 析构函数
    ~ChatServer() {
    }

    // 启动服务端
    void start() {
        // 开启事件循环处理
        _server.start();
    }

private:
    // 处理用户的连接创建和断开
    void onConnection(const muduo::net::TcpConnectionPtr &conn) {
        // 连接创建
        if (conn->connected()) {
            std::cout << "==> server " << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort()
                      << " state: online" << std::endl;
            conn->send("You have connected chat server");
        }
        // 连接断开
        else {
            std::cout << "==> server " << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort()
                      << " state: offline" << std::endl;
            // 断开连接（释放资源）
            conn->shutdown();
        }
    }

    // 处理用户读写事件（比如接收客户端发送的数据）
    void onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buffer, muduo::Timestamp time) {
        std::string message = buffer->retrieveAllAsString();
        std::cout << "==> server receive message: " << message << ", time: " << time.toFormattedString(false)
                  << std::endl;
    }

    muduo::net::TcpServer _server;
    muduo::net::EventLoop *_loop;
};
