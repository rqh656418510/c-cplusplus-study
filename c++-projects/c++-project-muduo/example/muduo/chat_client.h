#pragma once

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>

#include <iostream>
#include <string>

class ChatClient {
public:
    // 构造函数
    ChatClient(muduo::net::EventLoop* loop, const muduo::net::InetAddress& serverAddr, const std::string& nameArg)
        : _client(loop, serverAddr, nameArg), _loop(loop) {
        // 设置客户端TCP连接的回调
        _client.setConnectionCallback(std::bind(&ChatClient::onConnection, this, std::placeholders::_1));

        // 设置客户端接收数据的回调
        _client.setMessageCallback(std::bind(&ChatClient::onMessage, this, std::placeholders::_1, std::placeholders::_2,
                                             std::placeholders::_3));
    }

    // 析构函数
    ~ChatClient() {
        // 发起断开连接
        _client.disconnect();
        // 停止内部 Connector 的重连机制，避免异步行为
        _client.stop();
    }

    // 连接服务端
    void connect() {
        _client.connect();
    }

private:
    // 客户端绑定连接回调函数，当连接或者断开服务端时调用
    void onConnection(const muduo::net::TcpConnectionPtr& conn) {
        // 连接创建
        if (conn->connected()) {
            std::cout << "==> client " << conn->localAddress().toIpPort() << " -> " << conn->peerAddress().toIpPort()
                      << " state: connected" << std::endl;
        }
        // 连接断开
        else {
            std::cout << "==> client " << conn->localAddress().toIpPort() << " -> " << conn->peerAddress().toIpPort()
                      << " state: disconnected" << std::endl;
            // 断开连接（释放资源）
            conn->shutdown();
        }
    }

    // 客户端绑定消息回调函数，当有数据接收时调用
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time) {
        std::string message = buf->retrieveAllAsString();
        std::cout << "==> client receive message: " << message << ", time: " << time.toFormattedString(false)
                  << std::endl;
    }

    muduo::net::TcpClient _client;
    muduo::net::EventLoop* _loop;
};
