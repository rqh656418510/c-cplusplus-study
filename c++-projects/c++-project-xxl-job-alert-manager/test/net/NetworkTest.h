#pragma once

#include "Logger.h"
#include "Network.h"

// 网络测试
class NetworkTest {
public:
    // 获取公网IP地址
    void getPublicIp() {
        std::string ip = Network::getInstance().getPublicIp();
        LOG_INFO("public ip: %s", ip.c_str());
    }
};