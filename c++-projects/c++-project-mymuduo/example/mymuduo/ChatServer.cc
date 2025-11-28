/**
 * 基于 MyMuduo 网络库开发 TCP 服务器程序
 */

#include "ChatServer.h"

#include "Logger.h"

// 构造函数
ChatServer::ChatServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg)
    : server_(loop, listenAddr, nameArg), loop_(loop) {
    // 设置服务器注册用户连接的创建和断开回调
    server_.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));

    // 设置服务器注册用户读写事件的回调
    server_.setMessageCallback(
        std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置线程池的线程数量（比如：1个I/O线程，3个Worker线程）
    server_.setThreadNum(4);
}

// 析构函数
ChatServer::~ChatServer() {
}

// 启动服务器
void ChatServer::start() {
    // 开启事件循环处理
    server_.start();
}

// 处理用户的连接创建和断开
void ChatServer::onConnection(const TcpConnectionPtr &conn) {
    // 连接创建
    if (conn->connected()) {
        LOG_INFO("ChatServer - Connection UP : %s", conn->peerAddress().toIpPort().c_str());
    }
    // 连接断开
    else {
        LOG_INFO("ChatServer - Connection DOWN : %s", conn->peerAddress().toIpPort().c_str());
    }
}

// 处理用户读写事件（比如接收客户端发送的数据）
void ChatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time) {
    // 获取客户端发送的消息
    std::string message = buffer->retrieveAllAsString();

    // 去掉消息末尾的 '\r' 和 '\n' 字符（telnet 命令会发送 CRLF）
    while (!message.empty() && (message.back() == '\n' || message.back() == '\r')) {
        message.pop_back();
    }

    // 打印日志信息
    LOG_INFO("ChatServer - receive message: [%s], time: %s, ip: %s", message.c_str(), time.toString().c_str(),
             conn->peerAddress().toIpPort().c_str());

    // 发送数据给客户端
    conn->send("You just said: " + message + "\n");
}