#include "TcpServer.h"

// 构造函数
TcpServer::TcpServer(EventLoop* loop, const InetAddress& listenAddr, Option option) {
}

// 析构函数
TcpServer::~TcpServer() {
}

// 获取服务器监听的 IP 和端口信息
const std::string& TcpServer::ipPort() const {
    return ipPort_;
};

// 获取服务器名称
const std::string& TcpServer::name() const {
    return name_;
};

// 获取服务器的事件循环
EventLoop* TcpServer::getLoop() const {
    return loop_;
}

// 设置线程数量（即底层 subLoop 的数量）
void TcpServer::setThreadNum(int numThreads) {
}

// 启动服务器（线程安全）
void TcpServer::start() {
}

// 设置线程初始化回调操作
void TcpServer::setThreadInitCallback(const ThreadInitCallback& cb) {
    threadInitCallback = cb;
}

// 设置有新连接到来时的回调操作
void TcpServer::setConnectionCallback(const ConnectionCallback& cb) {
    connectionCallback_ = cb;
}

// 设置有数据到来时的回调操作
void TcpServer::setMessageCallback(const MessageCallback& cb) {
    messageCallback_ = cb;
}

// 设置数据发送完成时的回调操作
void TcpServer::setWriteCompleteCallback(const WriteCompleteCallback& cb) {
    writeCompleteCallback_ = cb;
}

// 创建 TCP 连接（非线程安全，在 EventLoop 上执行）
void TcpServer::newConnection(int sockfd, const InetAddress& peerAddr) {
}

// 移除 TCP 连接（线程安全）
void TcpServer::removeConnection(const TcpConnectionPtr& conn) {
}

// 在 EventLoop 上移除 TCP 连接（非线程安全）
void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn) {
}