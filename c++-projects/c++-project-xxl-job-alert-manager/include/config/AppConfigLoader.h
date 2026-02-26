#pragma once

#include "AppConfig.h"
#include "ConfigFileUtil.h"
#include "NonCopyable.h"
#include "unordered_map"

// 应用配置信息加载器（单例模式）
class AppConfigLoader : NonCopyable {
public:
    // 获取单例对象
    static AppConfigLoader& getInstance();

    // 获取全局配置
    const AppConfig& getConfig() const;

    // 全局的配置文件
    static std::string CONFIG_FILE;

private:
    // 私有构造函数
    AppConfigLoader();

    // 私有析构函数
    ~AppConfigLoader();

    // 加载配置文件内容
    AppConfig load(const char* configFile);

    // 配置参数转换为数字
    int toInt(const std::string& v, const char* key);

    // 配置参数转换为小数
    int toDubbo(const std::string& v, const char* key);

    // 配置参数转换为字符串
    std::string toStr(const std::string& v, const char* key);

    // 全局配置
    AppConfig config_;

    // 可选配置参数集合（非线程安全）
    std::unordered_map<std::string, std::string> optional_;
};