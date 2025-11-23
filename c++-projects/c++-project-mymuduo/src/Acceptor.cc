#include "Acceptor.h"

#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>

#include "InetAddress.h"
#include "Logger.h"

// 创建非阻塞的 listen fd
static int createNonblockingSocket() {
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (sockfd < 0) {
        LOG_FATAL("%s => create nonblock sockfd failed, errno:%d \n", __PRETTY_FUNCTION__, errno);
    }
    return sockfd;
}

// 构造函数
Acceptor::Acceptor(EventLoop* loop, const InetAddress& listenAddr, bool reuseport)
    : loop_(loop),
      acceptSocket_(createNonblockingSocket()),
      acceptChannel_(loop, acceptSocket_.fd()),
      listenning_(false) {
    acceptSocket_.setReuseAddr(true);
    acceptSocket_.setReusePort(reuseport);
    acceptSocket_.bindAddress(listenAddr);
    // 设置 acceptChannel_ 的读事件回调操作为 Acceptor::handleRead 方法
    acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead, this));
}

// 析构函数
Acceptor::~Acceptor() {
    // 关闭 acceptChannel_ 上的所有事件监听
    acceptChannel_.disableAll();
    // 从 Poller 中删除 acceptChannel_
    acceptChannel_.remove();
}

// 设置有新连接到来时的回调操作
void Acceptor::setNewConnectionCallback(const NewConnectionCallback& cb) {
    newConnectionCallback_ = cb;
}

// 监听连接请求（即监听有新的客户端连接进来）
void Acceptor::listen() {
    listenning_ = true;
    // 监听客户端的连接请求
    acceptSocket_.listen();
    // 启用 acceptChannel_ 的读事件监听（即监听有新连接到来）
    acceptChannel_.enableReading();
}

// 获取是否正在监听连接请求
bool Acceptor::listenning() const {
    return listenning_;
}

// 处理读事件（即处理有新客户端连接进来）
void Acceptor::handleRead() {
    InetAddress peerAddr;
    // 接受客户端新连接，返回新连接对应的 socket fd，用来和客户端进行读写
    int connfd = acceptSocket_.accept(&peerAddr);
    if (connfd >= 0) {
        // 有客户端新连接到来，执行回调操作（如果存在）
        if (newConnectionCallback_) {
            // 回调操作的职责：轮询找到 subLoop，将新客户端的 fd 分发给 subLoop，然后唤醒 subLoop 以处理该新客户端的连接
            newConnectionCallback_(connfd, peerAddr);
        } else {
            ::close(connfd);
        }
    } else {
        LOG_ERROR("%s => accept failed, errno:%d \n", __PRETTY_FUNCTION__, errno);
        if (errno == EMFILE) {
            LOG_ERROR("%s => sockfd reached limit \n", __PRETTY_FUNCTION__);
        }
    }
}