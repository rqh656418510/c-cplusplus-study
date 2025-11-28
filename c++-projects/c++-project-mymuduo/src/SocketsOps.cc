#include "SocketsOps.h"

#include <strings.h>

#include "Logger.h"

// 创建非阻塞的 Socket
int createNonblockingSocket() {
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (sockfd < 0) {
        LOG_FATAL("%s => create nonblock sockfd failed, errno:%d", __PRETTY_FUNCTION__, errno);
    }
    return sockfd;
}

// 获取 Socket 错误码
int getSocketError(int sockfd) {
    int optval;
    socklen_t optlen = sizeof optval;
    if (::getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0) {
        return errno;
    } else {
        return optval;
    }
}

// 获取本端地址
sockaddr_in getLocalAddr(int sockfd) {
    sockaddr_in localaddr;
    bzero(&localaddr, sizeof(localaddr));
    socklen_t addrlen = sizeof(localaddr);
    if (::getsockname(sockfd, (sockaddr*)(&localaddr), &addrlen) < 0) {
        LOG_ERROR("%s => get socket name failed, errno:%d", __PRETTY_FUNCTION__, errno);
    }
    return localaddr;
}

// 获取对端地址
sockaddr_in getPeerAddr(int sockfd) {
    sockaddr_in peeraddr;
    bzero(&peeraddr, sizeof(peeraddr));
    socklen_t addrlen = sizeof(peeraddr);
    if (::getpeername(sockfd, (sockaddr*)(&peeraddr), &addrlen) < 0) {
        LOG_ERROR("%s => get peer name failed, errno:%d", __PRETTY_FUNCTION__, errno);
    }
    return peeraddr;
}

// 判断是否为自连接
bool isSelfConnect(int sockfd) {
    sockaddr_in localaddr;
    sockaddr_in peeraddr;
    socklen_t addrlen = sizeof(sockaddr_in);

    // 获取本端地址
    if (getsockname(sockfd, (sockaddr*)&localaddr, &addrlen) < 0) {
        return false;
    }

    // 获取对端地址
    if (getpeername(sockfd, (sockaddr*)&peeraddr, &addrlen) < 0) {
        return false;
    }

    // 必须都是 IPv4
    if (localaddr.sin_family != AF_INET || peeraddr.sin_family != AF_INET) {
        return false;
    }

    // 检查 IP + 端口是否完全相同
    return (localaddr.sin_port == peeraddr.sin_port) && (localaddr.sin_addr.s_addr == peeraddr.sin_addr.s_addr);
}