#pragma once

#include "noncopyable.h"

// 类前置声明
class InetAddress;

class Socket : noncopyable {
public:
    // 构造函数
    explicit Socket(int sockFd);

    // 析构函数
    ~Socket();

    // 获取 socket 的文件描述符
    int fd() const;

    // 绑定地址
    void bindAddress(const InetAddress& localaddr);

    // 监听连接请求
    void listen();

    // 接受连接请求
    int accept(InetAddress* peeraddr);

    // 关闭写入
    void shutdownWrite();

    // 是否开启 TCP_NODELAY，开启后关闭 Nagle 算法，减少延迟
    void setTcpNoDelay(bool on);

    // 是否开启地址重用，允许端口在短时间内被重复绑定
    void setReuseAddr(bool on);

    // 是否开启端口重用，让多个进程/线程可以绑定同一端口
    void setReusePort(bool on);

    // 是否开启 TCP 保活，用于检测对端是否还存活
    void setKeepAlive(bool on);

private:
    const int sockFd_;  // socket 的文件描述符
};