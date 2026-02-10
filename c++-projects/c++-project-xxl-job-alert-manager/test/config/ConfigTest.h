#pragma once

#include "AppConfigLoader.h"
#include "Logger.h"

// 配置测试
class ConfigTest {
public:
    // 加载配置文件
    void loadConfigFile() {
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();
        LOG_INFO("DB IP: %s", config.mysql.ip.c_str());
        LOG_INFO("DB Port: %d", config.mysql.port);
    }
};