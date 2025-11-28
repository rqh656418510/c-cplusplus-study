/**
 * 基于 MyMuduo 网络库开发 TCP 客户端程序
 */

#include "ChatClient.h"

#include "Logger.h"

// 构造函数
ChatClient::ChatClient(EventLoop* loop, const InetAddress& serverAddr, const std::string& nameArg)
    : client_(loop, serverAddr, nameArg), loop_(loop) {
    // 允许重试连接
    client_.enableRetry();
    // 设置客户端TCP连接的回调
    client_.setConnectionCallback(std::bind(&ChatClient::onConnection, this, std::placeholders::_1));
    // 设置客户端接收数据的回调
    client_.setMessageCallback(
        std::bind(&ChatClient::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

// 析构函数
ChatClient::~ChatClient() {
    // 发起断开连接
    client_.disconnect();
    // 停止内部 Connector 的重连机制，避免异步行为
    client_.stop();
}

// 连接服务器
void ChatClient::connect() {
    client_.connect();
}

// 客户端绑定连接回调函数，当连接或者断开服务器时调用
void ChatClient::onConnection(const TcpConnectionPtr& conn) {
    // 连接创建
    if (conn->connected()) {
        // 打印日志信息
        LOG_INFO("ChatClient - new connection [%s] -> [%s], state: connected", conn->localAddress().toIpPort().c_str(),
                 conn->peerAddress().toIpPort().c_str());
        // 发送消息
        conn->send("I'm " + client_.name());
    }
    // 连接断开
    else {
        // 打印日志信息
        LOG_INFO("ChatClient - close connection [%s] -> [%s], state: disconnected",
                 conn->localAddress().toIpPort().c_str(), conn->peerAddress().toIpPort().c_str());
    }
}

// 客户端绑定消息回调函数，当有数据接收时调用
void ChatClient::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
    // 获取服务器发送的消息
    std::string message = buf->retrieveAllAsString();

    // 去掉消息末尾的 '\r' 和 '\n' 字符（nc 命令会发送 CRLF）
    while (!message.empty() && (message.back() == '\n' || message.back() == '\r')) {
        message.pop_back();
    }

    LOG_INFO("ChatClient - receive message: [%s], time: %s", message.c_str(), time.toString().c_str());
}
