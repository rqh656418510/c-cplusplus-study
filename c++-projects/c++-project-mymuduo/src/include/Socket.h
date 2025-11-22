#pragma once

#include "noncopyable.h"

// 类前置声明
class InetAddress;

class Socket : noncopyable {
public:
    // 构造函数
    explicit Socket(int socketFd);

    // 析构函数
    ~Socket();

private:
    const int socketFd_;
};