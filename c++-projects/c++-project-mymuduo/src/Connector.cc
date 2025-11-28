#include "Connector.h"

#include <assert.h>

#include "Channel.h"
#include "EventLoop.h"
#include "Logger.h"

// 构造函数
Connector::Connector(EventLoop* loop, const InetAddress& serverAddr)
    : loop_(loop), serverAddr_(serverAddr), connect_(false), state_(kDisconnected), retryDelayMs_(kInitRetryDelayMs) {
    LOG_DEBUG("%s => create connector at %p", __PRETTY_FUNCTION__, this);
}

// 析构函数
Connector::~Connector() {
    LOG_DEBUG("%s => destruct connector at %p", __PRETTY_FUNCTION__, this);
}

// 设置有新连接到来时的回调操作类型定义
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
    setState(kDisconnected);
    retryDelayMs_ = kInitRetryDelayMs;
    connect_ = true;
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
}

// 处理正在连接的 Socket
void Connector::connecting(int sockfd) {
}

// 处理写事件
void Connector::handleWrite() {
}

// 处理错误事件
void Connector::handleError() {
}

// 重试连接
void Connector::retry(int sockfd) {
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
    loop_->runInLoop(std::bind(&Connector::resetChannel, this));
    return sockfd;
}

// 重置 Channel
void Connector::resetChannel() {
    channel_.reset();
}