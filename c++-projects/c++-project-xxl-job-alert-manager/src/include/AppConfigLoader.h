#pragma once

#include "AppConfig.h"
#include "ConfigFileUtil.h"

// 应用配置信息加载器（单例对象）
class AppConfigLoader {
public:
    // 获取单例对象
    static AppConfigLoader& getInstance();

    // 获取全局配置
    const AppConfig getConfig() const;

    // 全局的配置文件路径
    static std::string CONFIG_FILE_PATH;

private:
    // 私有构造函数
    AppConfigLoader();

    // 私有析构函数
    ~AppConfigLoader();

    // 私有拷贝构造函数
    AppConfigLoader(const AppConfigLoader&) = default;

    // 私有赋值操作运算符
    AppConfigLoader& operator=(const AppConfigLoader&) = default;

    // 加载配置文件
    AppConfig load(const char* configFile);

    // 全局配置
    AppConfig config_;
};