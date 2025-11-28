#include "TcpClient.h"

#include <assert.h>

#include <chrono>
#include <functional>
#include <memory>
#include <thread>

#include "Connector.h"
#include "EventLoop.h"
#include "Logger.h"
#include "SocketsOps.h"

// 检查 EventLoop 指针是否为空
static EventLoop* CheckLoopNotNull(EventLoop* loop) {
    if (loop == nullptr) {
        LOG_FATAL("%s => eventloop is null", __PRETTY_FUNCTION__);
    }
    return loop;
}

namespace detail {

    // 移除 TCP 连接
    void removeConnection(EventLoop* loop, const TcpConnectionPtr& conn) {
        loop->queueInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
    }

    // 移除连接器
    void removeConnector(const ConnectorPtr& connector) {
    }

}  // namespace detail

// 构造函数
TcpClient::TcpClient(EventLoop* loop, const InetAddress& serverAddr, const std::string& nameArg)
    : loop_(CheckLoopNotNull(loop)),
      connector_(new Connector(loop_, serverAddr)),
      name_(nameArg),
      connectionCallback_(defaultConnectionCallback),
      messageCallback_(defaultMessageCallback),
      retry_(false),
      connect_(true),
      nextConnId_(1) {
    // 设置有新连接建立时的回调操作
    connector_->setNewConnectionCallback(std::bind(&TcpClient::newConnection, this, std::placeholders::_1));
    // 打印日志信息
    LOG_INFO("%s => crate tcp client [%s] - connector %p", __PRETTY_FUNCTION__, name_.c_str(), connector_.get());
}

// 析构函数
TcpClient::~TcpClient() {
    // 打印日志信息
    LOG_INFO("%s => destruct tcp client [%s] - connector %p", __PRETTY_FUNCTION__, name_.c_str(), connector_.get());

    // 获取当前 TcpConnection 的智能指针副本，并判断它是否是唯一拥有者
    TcpConnectionPtr conn;
    bool unique = true;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        unique = connection_.unique();
        conn = connection_;
    }

    if (conn) {
        assert(loop_ == conn->getLoop());
        // 设置 TCP 连接关闭时的回调操作
        CloseCallback cb = std::bind(&detail::removeConnection, loop_, std::placeholders::_1);
        loop_->runInLoop(std::bind(&TcpConnection::setCloseCallback, conn, cb));
        // 如果 TCP 连接唯一
        if (unique) {
            // 强制关闭 TCP 连接
            conn->forceClose();
        }
    } else {
        // 关闭连接器
        connector_->stop();
        // 获取当前的连接器
        auto connector = connector_;
        // 唤醒 loop_ 所在的线程去移除连接器
        loop_->runInLoop([connector]() { detail::removeConnector(connector); });
    }
}

// 发起连接
void TcpClient::connect() {
    // 打印日志信息
    LOG_INFO("%s => connect to %s", __PRETTY_FUNCTION__, connector_->serverAddress().toIpPort().c_str());
    // 标记需要连接
    connect_ = true;
    // 启动连接器
    connector_->start();
}

// 断开连接
void TcpClient::disconnect() {
    // 标记不需要连接
    connect_ = false;
    // 关闭当前 TCP 连接
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (connection_) {
            connection_->shutdown();
        }
    }
}

// 关闭客户端
void TcpClient::stop() {
    // 标记不需要连接
    connect_ = false;
    // 关闭连接器
    connector_->stop();
}

// 获取当前的 TCP 连接
TcpConnectionPtr TcpClient::connection() {
    std::unique_lock<std::mutex> lock(mutex_);
    return connection_;
}

// 获取事件循环
EventLoop* TcpClient::getLoop() const {
    return loop_;
}

// 是否允许重试连接
bool TcpClient::retry() const {
    return retry_;
}

// 允许重试连接
void TcpClient::enableRetry() {
    retry_ = true;
}

// 获取客户端名称
const std::string& TcpClient::name() const {
    return name_;
}

// 设置连接建立/关闭时的回调操作
void TcpClient::setConnectionCallback(ConnectionCallback cb) {
    connectionCallback_ = std::move(cb);
}

// 设置有数据到来时的回调操作
void TcpClient::setMessageCallback(MessageCallback cb) {
    messageCallback_ = std::move(cb);
}

// 设置数据发送完成时的回调操作
void TcpClient::setWriteCompleteCallback(WriteCompleteCallback cb) {
    writeCompleteCallback_ = std::move(cb);
}

// 创建新连接
void TcpClient::newConnection(int sockfd) {
    loop_->assertInLoopThread();

    // 远端地址
    InetAddress peerAddr(getPeerAddr(sockfd));

    // 拼接 TCP 连接的名称
    char buf[32] = {0};
    snprintf(buf, sizeof buf, ":%s#%d", peerAddr.toIpPort().c_str(), nextConnId_);
    ++nextConnId_;
    std::string connName = name_ + buf;

    // 本端地址
    InetAddress localAddr(getLocalAddr(sockfd));

    // 创建 TCP 连接对象
    TcpConnectionPtr conn(new TcpConnection(loop_, connName, sockfd, localAddr, peerAddr));

    // 设置 TCP 连接的回调操作
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    conn->setCloseCallback(std::bind(&TcpClient::removeConnection, this, std::placeholders::_1));

    // 设置当前的 TCP 连接
    {
        std::unique_lock<std::mutex> lock(mutex_);
        connection_ = conn;
    }

    // 建立连接
    conn->connectEstablished();
}

// 移除连接
void TcpClient::removeConnection(const TcpConnectionPtr& conn) {
    loop_->assertInLoopThread();
    assert(loop_ == conn->getLoop());

    // 重置当前的 TCP 连接
    {
        std::unique_lock<std::mutex> lock(mutex_);
        assert(connection_ == conn);
        connection_.reset();
    }

    // 唤醒 loop_ 所在的线程去销毁 TCP 连接
    loop_->queueInLoop(std::bind(&TcpConnection::connectDestroyed, conn));

    // 如果允许重试连接，且需要连接
    if (retry_ && connect_) {
        // 打印日志信息
        LOG_INFO("%s => tcp client [%s] reconnecting to %s", __PRETTY_FUNCTION__, name_.c_str(),
                 connector_->serverAddress().toIpPort().c_str());
        // 重启连接器
        connector_->restart();
    }
}