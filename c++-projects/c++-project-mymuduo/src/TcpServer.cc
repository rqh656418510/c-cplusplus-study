#include "TcpServer.h"

#include <string.h>

#include "Logger.h"

static EventLoop* CheckLoopNotNull(EventLoop* loop) {
    if (loop == nullptr) {
        LOG_FATAL("%s => baseLoop is null \n", __PRETTY_FUNCTION__);
    }
    return loop;
}

// 构造函数
TcpServer::TcpServer(EventLoop* loop, const InetAddress& listenAddr, const std::string nameArg, Option option)
    : loop_(CheckLoopNotNull(loop)),
      ipPort_(listenAddr.toIpPort()),
      name_(nameArg),
      acceptor_(new Acceptor(loop, listenAddr, option == kReusePort)),
      threadPool_(new EventLoopThreadPool(loop, name_)),
      connectionCallback_(defaultConnectionCallback),
      messageCallback_(defaultMessageCallback),
      nextConnId_(1) {
    // 当有新客户端连接进来时，会调用 TcpServer::newConnection() 函数
    acceptor_->setNewConnectionCallback(
        std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2));
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

// 设置线程池的线程数量（即底层 subLoop 的数量）
void TcpServer::setThreadNum(int numThreads) {
    threadPool_->setThreadNum(numThreads);
}

// 启动服务器（线程安全）
void TcpServer::start() {
    // 防止 TcpServer 被多次启动
    if (started_++ == 0) {
        // 启动多个子线程，并各自运行一个 subLoop
        threadPool_->start(threadInitCallback_);
        // 在 baseLoop（运行在主线程）上监听连接请求（即监听有新的客户端连接进来）
        loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));
    }
}

// 设置线程初始化回调操作
void TcpServer::setThreadInitCallback(const ThreadInitCallback& cb) {
    threadInitCallback_ = cb;
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

// 创建 TCP 连接（非线程安全，在 baseLoop 上执行）
void TcpServer::newConnection(int sockfd, const InetAddress& peerAddr) {
    // 获取下一个 subLoop（也称作 ioLoop）
    EventLoop* ioLoop = threadPool_->getNextLoop();
    // TODO
}

// 移除 TCP 连接（线程安全）
void TcpServer::removeConnection(const TcpConnectionPtr& conn) {
}

// 在 EventLoop 上移除 TCP 连接（非线程安全）
void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn) {
}