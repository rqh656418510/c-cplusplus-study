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

// 网络工具类（单例对象）
class Network {
public:
    // 获取单例对象
    static Network& getInstance();

    // 获取本地的 IP 地址，可指定网络接口名称（比如 eth0）
    std::string getLocalIp(const std::string& network_interface = "");

    // 获取公网 IP 地址
    std::string getPublicIp();

    // 删除拷贝构造函数
    Network(const Network&) = delete;

    // 删除赋值操作运算符
    Network& operator=(const Network&) = delete;

private:
    // 私有构造函数
    Network() = default;

    // 私有析构函数
    ~Network() = default;
};