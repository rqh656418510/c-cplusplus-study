#include "mprpcconfig.h"

// 加载配置文件
void MprpcConfig::LoadConfigFile(const char* config_file) {
}

// 获取配置项信息
std::string MprpcConfig::Load(const std::string& key) {
    return m_configMap.at(key);
}