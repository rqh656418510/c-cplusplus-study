#pragma once

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

#include "NonCopyable.h"

// 网络工具（单例模式）
class NetworkHelper : NonCopyable {
public:
    // 获取单例对象
    static NetworkHelper& getInstance();

    // 获取本地的 IP 地址，可指定网络接口名称（比如 eth0）
    std::string getLocalIp(const std::string& network_interface = "");

    // 获取公网 IP 地址
    std::string getPublicIp();

private:
    // 私有构造函数
    NetworkHelper() = default;

    // 私有析构函数
    ~NetworkHelper() = default;
};