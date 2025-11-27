/**
 * 基于 MyMuduo 网络库开发 TCP 服务端程序
 */

#include "EchoServer.h"

#include "Logger.h"

// 构造函数
EchoServer::EchoServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg)
    : server_(loop, listenAddr, nameArg), loop_(loop) {
    // 设置服务端注册用户连接的创建和断开回调
    // server_.setConnectionCallback(std::bind(&EchoServer::onConnection, this, std::placeholders::_1));

    // 设置服务端注册用户读写事件的回调
    // server_.setMessageCallback(
    // std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置线程池的线程数量（比如：1个I/O线程，3个Worker线程）
    server_.setThreadNum(4);
}

// 析构函数
EchoServer::~EchoServer() {
}

// 启动服务端
void EchoServer::start() {
    // 开启事件循环处理
    server_.start();
}

// 处理用户的连接创建和断开
void EchoServer::onConnection(const TcpConnectionPtr &conn) {
    // 连接创建
    if (conn->connected()) {
        LOG_INFO("Connection UP : %s", conn->peerAddress().toIpPort().c_str());
    }
    // 连接断开
    else {
        LOG_INFO("Connection DOWN : %s", conn->peerAddress().toIpPort().c_str());
    }
}

// 处理用户读写事件（比如接收客户端发送的数据）
void EchoServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time) {
    // 获取客户端发送的数据
    std::string message = buffer->retrieveAllAsString();

    // 去掉数据末尾的 '\r' 和 '\n' 字符（telnet 命令会发送 CRLF）
    while (!message.empty() && (message.back() == '\n' || message.back() == '\r')) {
        message.pop_back();
    }

    // 打印日志信息
    LOG_INFO("Echo server receive message, time: %s, content: %s", time.toString().c_str(), message.c_str());

    // 发送数据给客户端
    conn->send(message);

    // 关闭 TCP 连接（如果希望长连接，不要立即 shutdown）
    conn->shutdown();
}