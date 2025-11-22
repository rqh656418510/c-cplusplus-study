#include "Socket.h"

#include <errno.h>
#include <netinet/tcp.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "InetAddress.h"
#include "Logger.h"

// 构造函数
Socket::Socket(int sockFd) : sockFd_(sockFd) {
}

// 析构函数
Socket::~Socket() {
    ::close(sockFd_);
}

// 获取 socket 的文件描述符
int Socket::fd() const {
    return sockFd_;
}

// 绑定地址
void Socket::bindAddress(const InetAddress& localaddr) {
    if (0 != ::bind(sockFd_, (sockaddr*)localaddr.getSockAddr(), sizeof(sockaddr_in))) {
        LOG_FATAL("%s => bind socketFd:%d failed, errno:%d \n", __PRETTY_FUNCTION__, sockFd_, errno);
    }
}

// 监听连接请求
void Socket::listen() {
    if (0 != ::listen(sockFd_, SOMAXCONN)) {
        LOG_FATAL("%s => listen socketFd:%d failed, errno:%d \n", __PRETTY_FUNCTION__, sockFd_, errno);
    }
}

// 接受连接请求
int Socket::accept(InetAddress* peeraddr) {
    sockaddr_in addr;
    socklen_t len;
    bzero(&addr, sizeof addr);
    // 接受客户端新连接，返回新连接对应的 socket fd，用来和客户端进行读写
    int connfd = ::accept(sockFd_, (sockaddr*)&addr, &len);
    if (connfd >= 0) {
        peeraddr->setSockAddr(addr);
    }
    return connfd;
}

// 关闭写入
void Socket::shutdownWrite() {
    if (::shutdown(sockFd_, SHUT_WR) < 0) {
        LOG_FATAL("%s => shutdown write socketFd:%d failed, errno:%d \n", __PRETTY_FUNCTION__, sockFd_, errno);
    }
}

// 是否开启 TCP_NODELAY，开启后关闭 Nagle 算法，减少延迟
void Socket::setTcpNoDelay(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(sockFd_, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof optval));
}

// 是否开启地址重用，允许端口在短时间内被重复绑定
void Socket::setReuseAddr(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(sockFd_, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof optval));
}

// 是否开启端口重用，让多个进程/线程可以绑定同一端口
void Socket::setReusePort(bool on) {
    int optval = on ? 1 : 0;
    int ret = ::setsockopt(sockFd_, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof optval));
    if (ret < 0 && on) {
        LOG_FATAL("%s => set reuse port failed, errno:%d \n", __PRETTY_FUNCTION__, sockFd_, errno);
    }
}

// 是否开启 TCP 保活，用于检测对端是否还存活
void Socket::setKeepAlive(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(sockFd_, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t>(sizeof optval));
}
