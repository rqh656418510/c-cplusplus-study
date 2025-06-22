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
class NetworkUtil {
public:
    // 获取单例对象
    static NetworkUtil& GetInstance();

    // 获取本地的 IP 地址，可指定网络接口名称（比如 eth0）
    std::string FindLocalIp(const std::string& network_interface = "");

    // 获取一个未被占用的端口，可指定端口区间（比如 [7000, 9000]）
    int FindAvailablePort(int low = 7000, int high = 9000);

private:
    // 构造函数
    NetworkUtil() = default;

    // 删除拷贝构造函数
    NetworkUtil(const NetworkUtil&) = delete;

    // 删除赋值运算符
    NetworkUtil& operator=(const NetworkUtil&) = delete;
};