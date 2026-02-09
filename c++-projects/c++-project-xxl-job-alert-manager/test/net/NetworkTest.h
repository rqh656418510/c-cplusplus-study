#pragma once

#include "Logger.h"
#include "NetworkUtil.h"

// 网络测试
class NetworkTest {
public:
    // 获取公网IP地址
    void getPublicIp() {
        std::string ip = NetworkUtil::getInstance().getPublicIp();
        LOG_INFO("public ip: %s", ip.c_str());
    }
};