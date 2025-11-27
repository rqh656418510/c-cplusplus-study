#include "InetAddress.h"

#include <arpa/inet.h>
#include <string.h>
#include <strings.h>

// 构造函数
InetAddress::InetAddress(uint16_t port, std::string ip) {
    bzero(&addr_, sizeof addr_);
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}

// 构造函数
InetAddress::InetAddress(const sockaddr_in& addr) {
    this->addr_ = addr;
}

// 获取 IP 地址字符串
std::string InetAddress::toIp() const {
    char buf[64] = {0};
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
    return buf;
}

// 获取 IP 地址和端口号字符串（比如 127.0.0.1:8080）
std::string InetAddress::toIpPort() const {
    char buf[64] = {0};
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
    size_t end = strlen(buf);
    uint16_t port = ntohs(addr_.sin_port);
    sprintf(buf + end, ":%u", port);
    return buf;
}

// 获取端口号
uint16_t InetAddress::toPort() const {
    return ntohs(addr_.sin_port);
}

// 获取底层的 sockaddr_in 结构体指针
const sockaddr_in* InetAddress::getSockAddr() const {
    return &addr_;
}

// 设置底层的 sockaddr_in 结构体
void InetAddress::setSockAddr(const sockaddr_in& addr) {
    addr_ = addr;
}