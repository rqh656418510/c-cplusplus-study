#include "TcpServer.h"

#include <assert.h>
#include <string.h>

#include "Logger.h"
#include "TcpConnection.h"

static EventLoop* CheckLoopNotNull(EventLoop* loop) {
    if (loop == nullptr) {
        LOG_FATAL("%s => baseLoop is null", __PRETTY_FUNCTION__);
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
      nextConnId_(1),
      started_(0) {
    // 当有新客户端连接进来时，会调用 TcpServer::newConnection() 函数
    acceptor_->setNewConnectionCallback(
        std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2));
}

// 析构函数
TcpServer::~TcpServer() {
    // 打印日志信息
    LOG_DEBUG("%s => tcp server [%s] destructing", __PRETTY_FUNCTION__, name_.c_str());

    // 遍历所有 TCP 连接
    for (auto& item : connections_) {
        // 这个局部的智能指针对象出了右括号后，会自动释放掉对应的 TcpConnection 资源
        TcpConnectionPtr conn(item.second);
        // 重置原有的智能指针
        item.second.reset();
        // 唤醒 TCP 连接所在的 EventLoop 去执行 TcpConnection::connectDestroyed() 函数
        conn->getLoop()->runInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
    }
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

// 创建 TCP 连接（在 baseLoop 上执行）
void TcpServer::newConnection(int sockfd, const InetAddress& peerAddr) {
    // 通过轮询算法，获取下一个 subLoop（也称作 ioLoop）
    EventLoop* ioLoop = threadPool_->getNextLoop();

    // 拼接 TCP 连接的名称
    char buf[64] = {0};
    snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_;
    std::string connName = name_ + buf;

    // 打印日志信息
    LOG_DEBUG("%s => tcp server [%s] new connection [%s] from %s", __PRETTY_FUNCTION__, name_.c_str(), connName.c_str(),
              ipPort_.c_str());

    // 获取本地网络地址
    sockaddr_in local;
    ::bzero(&local, sizeof local);
    socklen_t addrlen = sizeof local;
    if (::getsockname(sockfd, (sockaddr*)&local, &addrlen) < 0) {
        LOG_ERROR("%s => fail to get local internet address", __PRETTY_FUNCTION__);
    }
    InetAddress localAddr(local);

    // 根据连接成功的 sockfd，创建 TCP 连接对象
    TcpConnectionPtr conn(new TcpConnection(ioLoop, connName, sockfd, localAddr, peerAddr));

    // 将新创建的 TCP 连接对象放进集合中
    connections_[connName] = conn;

    // 设置 TCP 连接的回调操作（由用户自定义）
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    conn->setCloseCallback(std::bind(&TcpServer::removeConnection, this, std::placeholders::_1));

    // 唤醒 ioLoop 所在的线程去执行 TcpConnection::connectEstablished() 函数
    ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished, conn));
}

// 移除 TCP 连接
void TcpServer::removeConnection(const TcpConnectionPtr& conn) {
    // 唤醒 baseLoop 所在的线程去执行 TcpServer::removeConnectionInLoop() 函数
    loop_->runInLoop(std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}

// 移除 TCP 连接（在 baseLoop 上执行）
void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn) {
    // 打印日志信息
    LOG_DEBUG("%s => tcp server [%s] remove connection [%s]", __PRETTY_FUNCTION__, name_.c_str(), conn->name().c_str());

    // 移除 TCP 连接
    size_t n = connections_.erase(conn->name());

    // 唤醒 TCP 连接所在的 EventLoop 去执行 TcpConnection::connectDestroyed() 函数
    assert(n == 1);
    EventLoop* ioLoop = conn->getLoop();
    ioLoop->runInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
}