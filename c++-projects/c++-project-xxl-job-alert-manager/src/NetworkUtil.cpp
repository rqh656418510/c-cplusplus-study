#include "NetworkUtil.h"

#include "Logger.h"

// 定义宏，启用 httplib 的 HTTPS 支持，需要依赖 OpenSSL
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

// 获取单例对象
NetworkUtil& NetworkUtil::getInstance() {
    // 静态局部变量（线程安全）
    static NetworkUtil instance;
    return instance;
}

// 获取本地的 IP 地址，可指定网络接口名称（比如 eth0）
std::string NetworkUtil::getLocalIp(const std::string& network_interface) {
    std::string result;

    // 获取本地网络接口的信息链表
    struct ifaddrs* ifaddr;
    if (getifaddrs(&ifaddr) == -1) {
        // Fallback 处理
        return "127.0.0.1";
    }

    // 遍历本地网络接口的信息链表
    for (auto* ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET) {
            continue;
        }

        // 获取网络接口的名称
        std::string name(ifa->ifa_name);

        // 跳过 lo 接口（回环接口）
        if (ifa->ifa_flags & IFF_LOOPBACK) {
            continue;
        }

        // 如果指定了网络接口（如 eth0），且匹配上了，就直接使用
        if (!network_interface.empty() && name == network_interface) {
            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr, ip, sizeof(ip));
            result = ip;
            break;
        }

        // 默认选择 eth0、ens33、enp0s3 等常见有线网卡
        if (network_interface.empty() && (name.find("eth") == 0 || name.find("en") == 0)) {
            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr, ip, sizeof(ip));
            result = ip;
            break;
        }
    }

    // 释放资源
    freeifaddrs(ifaddr);

    // 返回结果
    return result.empty() ? "127.0.0.1" : result;
}

// 获取公网 IP 地址
std::string NetworkUtil::getPublicIp() {
    try {
        // 创建 HTTPS 客户端
        httplib::SSLClient client("checkip.amazonaws.com", 443);

        // 设置连接超时时间（5秒）
        client.set_connection_timeout(5, 0);

        // 设置读取超时时间（5秒）
        client.set_read_timeout(5, 0);

        // 发送 GET 请求
        auto response = client.Get("/");

        // 检查响应状态
        if (response && response->status == 200) {
            // 获取响应体
            std::string body = response->body;

            // 移除末尾的换行符和空格
            while (!body.empty() && (body.back() == '\n' || body.back() == '\r' || body.back() == ' ')) {
                body.pop_back();
            }

            // 简单验证返回的是有效的 IP 地址格式
            if (!body.empty() && body.find('.') != std::string::npos) {
                return body;
            }
        }
    } catch (const std::exception& e) {
        LOG_ERROR("获取公网 IP 失败: %s", e.what());
    }

    // 如果获取失败，返回空字符串
    return "";
}