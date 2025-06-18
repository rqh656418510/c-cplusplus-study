#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

static const std::string RPC_SERVER_IP_KEY = "rpc-server-ip";
static const std::string RPC_SERVER_PORT_KEY = "rpc-server-port";
static const std::string ZK_SERVER_IP_KEY = "zk-server-ip";
static const std::string ZK_SERVER_PORT_KEY = "zk-server-port";

// RPC 框架读取配置文件的类
class MprpcConfig {
public:
    // 加载配置文件
    void LoadConfigFile(const char* config_file);

    // 获取配置项信息
    std::string Load(const std::string& key);

private:
    // 配置信息（无需考虑线程安全问题）
    std::unordered_map<std::string, std::string> m_configMap;

    // 去掉字符串前后的空白字符
    void Trim(std::string& str);
};