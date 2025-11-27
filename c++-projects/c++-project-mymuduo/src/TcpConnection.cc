#include "TcpConnection.h"

#include <assert.h>
#include <error.h>
#include <unistd.h>

#include "Channel.h"
#include "EventLoop.h"
#include "Logger.h"
#include "Socket.h"

static EventLoop* CheckLoopNotNull(EventLoop* loop) {
    if (loop == nullptr) {
        LOG_FATAL("%s => subLoop is null", __PRETTY_FUNCTION__);
    }
    return loop;
}

void defaultConnectionCallback(const TcpConnectionPtr& conn) {
    LOG_DEBUG("%s => %s -> %s is %s", __PRETTY_FUNCTION__, conn->localAddress().toIpPort().c_str(),
              conn->peerAddress().toIpPort().c_str(), (conn->connected() ? "UP" : "DOWN"));
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
    // 给 Channel 设置相应的回调函数，Poller 会通知 Channel 它感兴趣的事件发生了，然后 Channel 会回调相应的操作函数
    channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    channel_->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallback(std::bind(&TcpConnection::handleError, this));
    // 打印日志信息
    LOG_DEBUG("%s => create tcp connection [%s] at %p, fd=%d", __PRETTY_FUNCTION__, name_.c_str(), this, sockfd);
    // 开启 TCP 保活机制
    socket_->setKeepAlive(true);
}

// 析构函数
TcpConnection::~TcpConnection() {
    // 打印日志信息
    LOG_DEBUG("%s => destruct tcp connection [%s] at %p, fd=%d, state=%s", __PRETTY_FUNCTION__, name_.c_str(), this,
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

// 发送数据到输出缓冲区
void TcpConnection::send(const std::string& message) {
    if (state_ == kConnected) {
        // 如果当前线程是 loop_ 所在的线程
        if (loop_->isInLoopThread()) {
            // 直接将数据发送到输出缓冲区
            sendInLoop(message.c_str(), message.size());
        } else {
            // 唤醒 loop_ 对应的线程将数据发送到输出缓冲区
            loop_->runInLoop(std::bind(&TcpConnection::sendInLoop, this, message.c_str(), message.size()));
        }
    }
}

// 关闭 TCP 连接
void TcpConnection::shutdown() {
    if (state_ == kConnected) {
        // 设置 TCP 连接的状态
        setState(kDisconnecting);
        // 唤醒 loop_ 对应的线程去关闭 TCP 连接
        loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, this));
    }
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

// 设置触发高水位时的回调操作
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
Buffer* TcpConnection::outputBuffer() {
    return &outputBuffer_;
}

// 连接建立
void TcpConnection::connectEstablished() {
    assert(state_ == kConnecting);
    // 设置 TCP 连接的状态
    setState(kConnected);
    // Channel 绑定 TCP 连接
    channel_->tie(shared_from_this());
    // Channel 开启监听 fd 上的读事件
    channel_->enableReading();
    // 调用用户设置的回调操作
    connectionCallback_(shared_from_this());
}

// 连接销毁
void TcpConnection::connectDestroyed() {
    if (state_ == kConnected) {
        // 设置 TCP 连接的状态
        setState(kDisconnected);
        // Channel 禁止监听 fd 上的所有事件
        channel_->disableAll();
        // 调用用户设置的回调操作
        connectionCallback_(shared_from_this());
    }
    // 从 Poller 中删除 Channel
    channel_->remove();
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
        LOG_ERROR("%s => read fd error, fd=%d, errno=%d", __PRETTY_FUNCTION__, channel_->fd(), errno);
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
                    // 唤醒 loop_ 所在的线程去执行用户设置的回调操作
                    loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
                }
                // 如果正在断开 TCP 连接，则关闭 TCP 连接
                if (state_ == kDisconnecting) {
                    shutdownInLoop();
                }
            }
        } else if (n < 0) {
            // 打印日志信息
            LOG_ERROR("%s => write fd error, fd=%d, errno=%d", __PRETTY_FUNCTION__, channel_->fd(), errno);
        }
    } else {
        // 打印日志信息
        LOG_DEBUG("%s => tcp connection [%s] is down, no more writing, fd=%d", __PRETTY_FUNCTION__, name_.c_str(),
                  channel_->fd());
    }
}

// 处理关闭事件
void TcpConnection::handleClose() {
    // 打印日志信息
    LOG_DEBUG("%s => tcp connection [%s] is close, fd=%d, state=%s", __PRETTY_FUNCTION__, name_.c_str(), channel_->fd(),
              stateToString());

    // 设置 TCP 连接的状态
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
    LOG_ERROR("%s => tcp connection [%s] occurred error, fd=%d, SO_ERROR:%d", __PRETTY_FUNCTION__, name_.c_str(),
              channel_->fd(), saveErrno);
}

// 在事件循环（EventLoop）中发送数据到输出缓冲区
void TcpConnection::sendInLoop(const void* message, size_t len) {
    // 已发送数据的字节数
    ssize_t nwrote = 0;

    // 剩下未发送数据的字节数
    size_t remaining = len;

    // 是否发生致命错误
    bool faultError = false;

    // 如果 TCP 连接已断开，则放弃发送数据
    if (state_ == kDisconnected) {
        LOG_ERROR("%s => tcp connection [%s] disconnected, give up writing", __PRETTY_FUNCTION__, name_.c_str());
        return;
    }

    // 如果 Channel 是第一次写入数据，且输出缓冲区里面没有待发送的数据
    if (!channel_->isWriting() && outputBuffer_.readableBytes() == 0) {
        // 直接发送数据（成功：返回已发送的字节数，失败：返回小于零的数字）
        nwrote = ::write(channel_->fd(), message, len);
        // 发送数据成功
        if (nwrote >= 0) {
            // 剩下未发送的字节数
            remaining = len - nwrote;
            // 如果所有数据都发送完
            if (remaining == 0 && writeCompleteCallback_) {
                // 唤醒 loop_ 所在的线程去执行用户设置的回调操作
                loop_->runInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
            }
        }
        // 发送数据失败
        else {
            nwrote = 0;
            if (errno != EWOULDBLOCK) {
                LOG_ERROR("%s => occurred error", __PRETTY_FUNCTION__);
                if (errno == EPIPE || errno == ECONNRESET) {
                    faultError = true;
                }
            }
        }
    }

    assert(remaining <= len);

    // 如果发送数据没有发生致命错误，且有剩下的数据未发送
    if (!faultError && remaining > 0) {
        // 输出缓冲区中原先未发送数据的字节数
        size_t oldLen = outputBuffer_.readableBytes();
        // 判断所有未发送数据的大小是否触及了高水位线
        if (oldLen + remaining >= highWaterMark_ && oldLen < highWaterMark_ && highWaterMarkCallback_) {
            // 唤醒 loop_ 所在的线程去执行用户设置的回调操作
            loop_->runInLoop(std::bind(highWaterMarkCallback_, shared_from_this(), oldLen + remaining));
        }
        // 往输出缓冲区中写入上面未发送完的数据
        outputBuffer_.append(static_cast<const char*>(message) + nwrote, remaining);
        // 让 Channel 开启监听 fd 上的写事件
        if (!channel_->isWriting()) {
            channel_->enableWriting();
        }
    }
}

// 在事件循环（EventLoop）中关闭 TCP 连接
void TcpConnection::shutdownInLoop() {
    // 如果输出缓冲区中的所有数据都发送完
    if (!channel_->isWriting()) {
        // Socket 关闭写入
        socket_->shutdownWrite();
    }
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