#include "networkutil.h"

// 获取单例对象
NetworkUtil& NetworkUtil::GetInstance() {
    // 局部静态变量（线程安全）
    static NetworkUtil instance;
    return instance;
}

// 获取本地的 IP 地址，可指定网络接口名称（比如 eth0）
std::string NetworkUtil::FindLocalIp(const std::string& network_interface) {
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

// 获取一个未被占用的端口（可指定端口区间，比如 [7000, 9000]）
int NetworkUtil::FindAvailablePort(int low, int high) {
    // 遍历指定区间内的所有端口
    for (int port = low; port <= high; ++port) {
        // 创建一个 IPv4 TCP Socket
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            // 创建 Socket 失败，尝试下一个端口
            continue;
        }

        // 初始化 Socket 地址，绑定到任意本地地址（0.0.0.0）和当前端口
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;  // 0.0.0.0
        addr.sin_port = htons(port);

        // 设置 Socket 选项：SO_REUSEADDR 允许端口重复绑定（避免 TIME_WAIT 问题）
        int opt = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        // 尝试将 Socket 绑定到指定端口
        if (bind(sockfd, (sockaddr*)&addr, sizeof(addr)) == 0) {
            // 绑定成功，释放资源（因为这里只是探测端口是否可用）
            close(sockfd);
            // 返回找到的可用端口
            return port;
        }

        // 端口绑定失败，说明端口已被占用或其他错误，释放资源
        close(sockfd);
    }

    // 遍历完指定的端口区间，没有找到可用端口，返回 -1 表示失败
    return -1;
}