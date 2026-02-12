#include "NetworkHelper.h"

#include <curl/curl.h>

#include "CurlHelper.h"
#include "Logger.h"

// 获取单例对象
NetworkHelper& NetworkHelper::getInstance() {
    // 静态局部变量（线程安全）
    static NetworkHelper instance;
    return instance;
}

// 获取本地的 IP 地址，可指定网络接口名称（比如 eth0）
std::string NetworkHelper::getLocalIp(const std::string& network_interface) {
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
std::string NetworkHelper::getPublicIp() {
    try {
        // 创建Curl对象
        CURL* curl = curl_easy_init();
        if (!curl) {
            LOG_ERROR("Curl Init Failed");
            return "";
        }

        std::string response_str;
        const std::string url = "https://checkip.amazonaws.com/";

        // 设置Curl选项
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_str);  // 写回调的目标对象
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);               // 设置请求超时时间为5秒（单位：秒）
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);        // 启用对服务器SSL证书的验证
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);  // 验证服务器证书中的主机名是否与请求URL匹配

        // 发送GET请求
        CURLcode res = curl_easy_perform(curl);

        // 获取HTTP状态码
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

        // 检查请求是否成功
        if (res != CURLE_OK) {
            LOG_ERROR("Get public ip failed: %s", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            return "";
        }

        if (http_code != 200) {
            LOG_ERROR("Get public ip failed, http code: %ld", http_code);
            curl_easy_cleanup(curl);
            return "";
        }

        // 清理资源
        curl_easy_cleanup(curl);

        // 移除响应体末尾的换行符和空格
        while (!response_str.empty() &&
               (response_str.back() == '\n' || response_str.back() == '\r' || response_str.back() == ' ')) {
            response_str.pop_back();
        }

        // 简单验证返回的是有效的IP地址格式
        if (!response_str.empty() && response_str.find('.') != std::string::npos) {
            return response_str;
        }
    } catch (const std::exception& e) {
        LOG_ERROR("Get public ip failed, exception: %s", e.what());
    } catch (...) {
        LOG_ERROR("Get public ip failed, unknown exception");
    }

    // 如果获取失败，返回空字符串
    return "";
}