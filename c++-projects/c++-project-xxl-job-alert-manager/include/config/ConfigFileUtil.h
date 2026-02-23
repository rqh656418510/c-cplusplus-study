#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "NonCopyable.h"

// 读取配置文件（INI格式）的工具类
class ConfigFileUtil : NonCopyable {
public:
    // 加载配置文件（INI格式）
    void loadConfigFile(const char* config_file);

    // 获取配置项信息
    std::string load(const std::string& key);

private:
    // 配置信息集合（非线程安全）
    std::unordered_map<std::string, std::string> m_configMap;

    // 去掉字符串前后的空白字符
    void trim(std::string& str);
};