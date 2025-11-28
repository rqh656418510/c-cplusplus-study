#include "Connector.h"

#include <assert.h>
#include <error.h>
#include <sys/socket.h>
#include <unistd.h>

#include <chrono>
#include <thread>

#include "Channel.h"
#include "EventLoop.h"
#include "Logger.h"
#include "SocketsOps.h"

// 定义初始重试延迟时间（毫秒）
const int Connector::kInitRetryDelayMs = 500;
// 定义最大重试延迟时间（毫秒）
const int Connector::kMaxRetryDelayMs = 30 * 1000;

// 构造函数
Connector::Connector(EventLoop* loop, const InetAddress& serverAddr)
    : loop_(loop), serverAddr_(serverAddr), connect_(false), state_(kDisconnected), retryDelayMs_(kInitRetryDelayMs) {
    // 打印日志信息
    LOG_DEBUG("%s => create connector at %p", __PRETTY_FUNCTION__, this);
}

// 析构函数
Connector::~Connector() {
    // 打印日志信息
    LOG_DEBUG("%s => destruct connector at %p", __PRETTY_FUNCTION__, this);
}

// 设置有新连接建立时的回调操作类型定义
void Connector::setNewConnectionCallback(const NewConnectionCallback& cb) {
    newConnectionCallback_ = cb;
}

// 启动连接器
void Connector::start() {
    // 标记需要连接
    connect_ = true;
    // 唤醒 loop_ 对应的线程去启动连接器
    loop_->runInLoop(std::bind(&Connector::startInLoop, this));
}

// 在 EventLoop 所处的线程上启动连接器
void Connector::startInLoop() {
    loop_->assertInLoopThread();
    assert(state_ == kDisconnected);
    // 判断是否需要连接
    if (connect_) {
        // 发起连接操作
        connect();
    } else {
        LOG_DEBUG("%s => do not connect");
    }
}

// 停止连接器
void Connector::stop() {
    // 标记不再连接
    connect_ = false;
    // 唤醒 loop_ 对应的线程去关闭连接器
    loop_->queueInLoop(std::bind(&Connector::stopInLoop, this));
}

// 在 EventLoop 所处的线程上停止连接器
void Connector::stopInLoop() {
    loop_->assertInLoopThread();
    if (state_ == kConnecting) {
        // 设置连接状态为已断开
        setState(kDisconnected);
        // 移除并重置 Channel
        int sockfd = removeAndResetChannel();
        // 重试连接
        retry(sockfd);
    }
}

// 重启连接器（必须在 EventLoop 所处的线程上执行）
void Connector::restart() {
    loop_->assertInLoopThread();
    // 设置连接状态
    setState(kDisconnected);
    // 重置重试延迟时间
    retryDelayMs_ = kInitRetryDelayMs;
    // 标记需要连接
    connect_ = true;
    // 启动连接器
    startInLoop();
}

// 获取服务器地址
const InetAddress& Connector::serverAddress() const {
    return serverAddr_;
}

// 设置连接状态
void Connector::setState(States s) {
    state_ = s;
}

// 发起连接操作
void Connector::connect() {
    // 创建非阻塞的 Socket
    int sockfd = createNonblockingSocket();
    // 连接 TCP 服务器
    int ret = ::connect(sockfd, (sockaddr*)serverAddr_.getSockAddr(), sizeof(sockaddr_in));
    // 处理连接结果
    int savedErrno = (ret == 0) ? 0 : errno;
    switch (savedErrno) {
        case 0:
        case EINPROGRESS:
        case EINTR:
        case EISCONN:
            // 处理正在连接的 Socket
            connecting(sockfd);
            break;

        case EAGAIN:
        case EADDRINUSE:
        case EADDRNOTAVAIL:
        case ECONNREFUSED:
        case ENETUNREACH:
            // 重新连接
            retry(sockfd);
            break;

        case EACCES:
        case EPERM:
        case EAFNOSUPPORT:
        case EALREADY:
        case EBADF:
        case EFAULT:
        case ENOTSOCK:
            // 打印日志信息
            LOG_ERROR("%s => connect error, errno:%d", __PRETTY_FUNCTION__, errno);
            // 关闭连接
            ::close(sockfd);
            break;

        default:
            // 打印日志信息
            LOG_ERROR("%s => unexpected error, errno:%d", __PRETTY_FUNCTION__, errno);
            // 关闭连接
            ::close(sockfd);
            break;
    }
}

// 处理正在连接的 Socket
void Connector::connecting(int sockfd) {
    // 设置连接状态为正在连接
    setState(kConnecting);
    // 创建 Channel 并注册写事件和错误事件的回调操作
    channel_.reset(new Channel(loop_, sockfd));
    channel_->setWriteCallback(std::bind(&Connector::handleWrite, this));
    channel_->setErrorCallback(std::bind(&Connector::handleError, this));
    // Channel 开启监听 fd 上的写事件
    channel_->enableWriting();
}

// 处理写事件
void Connector::handleWrite() {
    // 打印日志信息
    LOG_DEBUG("%s => state:%d", __PRETTY_FUNCTION__, state_);

    if (state_ == kConnecting) {
        // 移除并重置 Channel
        int sockfd = removeAndResetChannel();
        // 获取 Socket 错误码
        int savedErrno = getSocketError(sockfd);

        // 发生错误
        if (savedErrno) {
            // 打印日志信息
            LOG_WARN("%s => SO_ERROR=%d", __PRETTY_FUNCTION__, savedErrno);
            // 重新连接
            retry(sockfd);
        }
        // 发生自连接
        else if (isSelfConnect(sockfd)) {
            // 打印日志信息
            LOG_WARN("%s => self connect", __PRETTY_FUNCTION__);
            // 重新连接
            retry(sockfd);
        }
        // 连接成功
        else {
            // 设置连接状态为已连接
            setState(kConnected);
            // 判断是否需要连接
            if (connect_) {
                // 需要连接，执行有新连接建立时的回调操作
                newConnectionCallback_(sockfd);
            } else {
                // 不需要连接，关闭该连接
                ::close(sockfd);
            }
        }
    } else {
        assert(state_ == kDisconnected);
    }
}

// 处理错误事件
void Connector::handleError() {
    // 打印日志信息
    LOG_ERROR("%s => occurred error, state:%d", __PRETTY_FUNCTION__, state_);

    if (state_ == kConnecting) {
        // 移除并重置 Channel
        int sockfd = removeAndResetChannel();
        // 获取 Socket 错误码
        int savedErrno = getSocketError(sockfd);
        // 打印日志信息
        LOG_DEBUG("%s => SO_ERROR:%d", __PRETTY_FUNCTION__, savedErrno);
        // 重新连接
        retry(sockfd);
    }
}

// 重试连接
void Connector::retry(int sockfd) {
    // 关闭连接
    ::close(sockfd);

    // 设置连接状态
    setState(kDisconnected);

    // 判断是否需要连接
    if (connect_) {
        // 获取当前的重试延迟时间
        int delay = retryDelayMs_;

        // 获取 shared_ptr 指向的自身对象
        auto self = shared_from_this();

        // 打印日志信息
        LOG_INFO("%s => retry connecting to %s in %d milliseconds", __PRETTY_FUNCTION__, serverAddr_.toIpPort().c_str(),
                 delay);

        // 在一个独立的线程中等待一段时间后启动连接器
        std::thread([self, delay]() {
            // 等待一段时间
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            // 唤醒 loop_ 对应的线程去启动连接器
            self->loop_->queueInLoop([self]() { self->startInLoop(); });
        }).detach();

        // 指数退避算法，增加重试延迟时间
        retryDelayMs_ = std::min(retryDelayMs_ * 2, kMaxRetryDelayMs);
    } else {
        LOG_DEBUG("%s => do not connect", __PRETTY_FUNCTION__);
    }
}

// 移除并重置 Channel
int Connector::removeAndResetChannel() {
    // 禁用 Channel 的所有事件监听
    channel_->disableAll();
    // 从 Poller 中删除 Channel
    channel_->remove();
    // 获取 Channel 对应的 sockfd
    int sockfd = channel_->fd();
    // 唤醒 loop_ 对应的线程去重置 Channel
    loop_->queueInLoop(std::bind(&Connector::resetChannel, this));
    return sockfd;
}

// 重置 Channel
void Connector::resetChannel() {
    channel_.reset();
}