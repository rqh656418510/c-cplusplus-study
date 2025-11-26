#include "TcpConnection.h"

#include <error.h>

#include "Channel.h"
#include "EventLoop.h"
#include "Logger.h"
#include "Socket.h"

static EventLoop* CheckLoopNotNull(EventLoop* loop) {
    if (loop == nullptr) {
        LOG_FATAL("%s => subLoop is null \n", __PRETTY_FUNCTION__);
    }
    return loop;
}

void defaultConnectionCallback(const TcpConnectionPtr& conn) {
    LOG_INFO("%s => %s -> %s is %s", __PRETTY_FUNCTION__, conn->localAddress().toIpPort(),
             conn->peerAddress().toIpPort(), (conn->connected() ? "UP" : "DOWN"));
}

void defaultMessageCallback(const TcpConnectionPtr&, Buffer* buf, Timestamp) {
    buf->retrieveAll();
}

// 构造函数
TcpConnection::TcpConnection(EventLoop* loop, const std::string& nameArg, int sockfd, const InetAddress& localAddr,
                             const InetAddress& peerAddr)
    : loop_(CheckLoopNotNull(loop)),
      name_(nameArg),
      state_(kConnecting),
      socket_(new Socket(sockfd)),
      channel_(new Channel(loop, sockfd)),
      localAddr_(localAddr),
      peerAddr_(peerAddr),
      connectionCallback_(defaultConnectionCallback),
      messageCallback_(defaultMessageCallback),
      highWaterMark_(64 * 1024 * 1024) {
    // 给 Channel 设置相应的回调函数，Poller 会通知 Channel 它感兴趣的事件发生了，Channel 会回调相应的操作函数
    channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    channel_->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallback(std::bind(&TcpConnection::handleError, this));
    // 打印日志信息
    LOG_DEBUG("%s => create tcp connection %s at %p, fd=%d \n", __PRETTY_FUNCTION__, name_.c_str(), this, sockfd);
    // 开启 TCP 保活机制
    socket_->setKeepAlive(true);
}

// 析构函数
TcpConnection::~TcpConnection() {
    // 打印日志信息
    LOG_DEBUG("%s => destruct tcp connection %s at %p, fd=%d, state=%s \n", __PRETTY_FUNCTION__, name_.c_str(), this,
              channel_->fd(), stateToString());
}

// 获取 TCP 连接所在的事件循环
EventLoop* TcpConnection::getLoop() const {
    return loop_;
}

// 获取 TCP 连接的名称
const std::string& TcpConnection::name() const {
    return name_;
}

// 获取 TCP 连接的本地网络地址
const InetAddress& TcpConnection::localAddress() const {
    return localAddr_;
}

// 获取 TCP 连接的远程网络地址
const InetAddress& TcpConnection::peerAddress() const {
    return peerAddr_;
}

// 判断 TCP 连接是否处于已连接状态
bool TcpConnection::connected() const {
    return state_ == kConnected;
}

// 判断 TCP 连接是否处于断开状态
bool TcpConnection::disconnected() const {
    return state_ == kDisconnected;
}

// 发送数据
void TcpConnection::send(const void* message, int len) {
}

// 关闭 TCP 连接
void TcpConnection::shutdown() {
}

// 连接建立/关闭时的回调操作
void TcpConnection::setConnectionCallback(const ConnectionCallback& cb) {
    connectionCallback_ = cb;
}

// 设置有数据到来时的回调操作
void TcpConnection::setMessageCallback(const MessageCallback& cb) {
    messageCallback_ = cb;
}

// 设置数据发送完成时的回调操作
void TcpConnection::setWriteCompleteCallback(const WriteCompleteCallback& cb) {
    writeCompleteCallback_ = cb;
}

// 设置高水位时的回调操作
void TcpConnection::setHighWaterMarkCallback(const HighWaterMarkCallback& cb, size_t highWaterMark) {
    highWaterMarkCallback_ = cb;
    highWaterMark_ = highWaterMark;
}

// 设置连接关闭时的回调操作
void TcpConnection::setCloseCallback(const CloseCallback& cb) {
    closeCallback_ = cb;
}

// 获取输入缓冲区
Buffer* TcpConnection::inputBuffer() {
    return &inputBuffer_;
}

// 获取输出缓冲区
Buffer* TcpConnection::outBuffer() {
    return &outputBuffer_;
}

// 连接建立
void TcpConnection::connectEstablished() {
}

// 连接销毁
void TcpConnection::connectDestroyed() {
}

// 处理读事件
void TcpConnection::handleRead(Timestamp receiveTime) {
    // 临时错误码
    int saveErrno = 0;

    // 从 fd 上读取数据，并写入到输入缓冲区中
    ssize_t n = inputBuffer_.readFd(channel_->fd(), &saveErrno);

    if (n > 0) {
        // 已建立连接的客户端，有可读事件发生了，调用用户设置的回调操作
        messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
    } else if (n == 0) {
        // 处理连接关闭
        handleClose();
    } else {
        // 设置错误码
        errno = saveErrno;
        // 打印日志信息
        LOG_ERROR("%s => read fd error, fd=%d, errno=%d \n", __PRETTY_FUNCTION__, channel_->fd(), errno);
        // 处理连接错误
        handleError();
    }
}

// 处理写事件
void TcpConnection::handleWrite() {
    // 判断 Channel 是否正在监听写事件
    if (channel_->isWriting()) {
        // 临时错误码
        int saveErrno = 0;

        // 从输出缓冲区读取数据，并写入到 fd 上
        ssize_t n = outputBuffer_.writeFd(channel_->fd(), &saveErrno);

        if (n > 0) {
            // 移动输出缓冲区的读指针（标记有哪些数据被发送了）
            outputBuffer_.retrieve(n);

            // 如果输出缓冲区中的所有数据都发送完了
            if (outputBuffer_.readableBytes() == 0) {
                // 关闭监听 fd 上的写事件
                channel_->disableWriting();
                // 调用用户设置的回调操作
                if (writeCompleteCallback_) {
                    // 唤醒 loop_ 对应的线程去执行用户设置的回调操作
                    loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
                }
                // 如果正在断开 TCP 连接，则关闭 TCP 连接
                if (state_ == kDisconnecting) {
                    shutdownInLoop();
                }
            }
        } else if (n < 0) {
            // 打印日志信息
            LOG_ERROR("%s => write fd error, fd=%d, errno=%d \n", __PRETTY_FUNCTION__, channel_->fd(), errno);
        }
    } else {
        // 打印日志信息
        LOG_DEBUG("%s => connection %s is down, no more writing, fd=%d \n", __PRETTY_FUNCTION__, name_.c_str(),
                  channel_->fd());
    }
}

// 处理关闭事件
void TcpConnection::handleClose() {
    // 打印日志信息
    LOG_DEBUG("%s => connection %s close, fd=%d, state=%s \n", __PRETTY_FUNCTION__, name_.c_str(), channel_->fd(),
              stateToString());

    // 设置连接状态
    setState(kDisconnected);

    // 禁止 Channel 监听 fd 上的所有事件
    channel_->disableAll();

    // 获取当前的 TCP 连接
    TcpConnectionPtr guardThis(shared_from_this());

    // 调用用户设置的连接建立/关闭时的回调操作
    connectionCallback_(guardThis);

    // 调用用户设置的连接关闭时的回调操作
    if (closeCallback_) {
        closeCallback_(guardThis);
    }
}

// 处理错误事件
void TcpConnection::handleError() {
    int saveErrno = 0;

    int optval;
    socklen_t optlen = sizeof optval;
    if (::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0) {
        saveErrno = errno;
    } else {
        saveErrno = optval;
    }

    // 打印日志信息
    LOG_ERROR("%s => connection name=%s occurred error, fd=%d, SO_ERROR:%d \n", __PRETTY_FUNCTION__, name_.c_str(),
              channel_->fd(), saveErrno);
}

// 在事件循环（EventLoop）中发送数据
void TcpConnection::sendInLoop(const void* message, size_t len) {
}

// 在事件循环（EventLoop）中关闭 TCP 连接
void TcpConnection::shutdownInLoop() {
}

// 设置 TCP 连接的状态
void TcpConnection::setState(StateE state) {
    state_ = state;
}

// 将 TCP 连接的状态转换为字符串
const char* TcpConnection::stateToString() const {
    switch (state_) {
        case kDisconnected:
            return "kDisconnected";
        case kConnecting:
            return "kConnecting";
        case kConnected:
            return "kConnected";
        case kDisconnecting:
            return "kDisconnecting";
        default:
            return "unknown state";
    }
}