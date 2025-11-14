#pragma once

#include <netinet/in.h>

#include <iostream>

class InetAddress {
public:
    explicit InetAddress(uint16_t port = 0, std::string ip = "127.0.0.1");
    explicit InetAddress(const sockaddr_in& addr);

    std::string toIp() const;
    std::string toIpPort() const;
    uint16_t toPort() const;
    const sockaddr_in* getSockAddr() const;

private:
    sockaddr_in addr_;
};