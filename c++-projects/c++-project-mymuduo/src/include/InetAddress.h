#pragma once

#include <netinet/in.h>

#include <iostream>

#include "copyable.h"

// 网络地址类
class InetAddress : public copyable {
public:
    // 构造函数
    explicit InetAddress(uint16_t port = 0, std::string ip = "127.0.0.1");

    // 构造函数
    explicit InetAddress(const sockaddr_in& addr);

    // 获取 IP 地址字符串
    std::string toIp() const;

    // 获取 IP 地址和端口号字符串（比如 127.0.0.1:8080）
    std::string toIpPort() const;

    // 获取端口号
    uint16_t toPort() const;

    // 获取底层的 sockaddr_in 结构体指针
    const sockaddr_in* getSockAddr() const;

private:
    sockaddr_in addr_;  // 底层的 sockaddr_in 结构体
};