#pragma once

#include "mprpcconfig.h"

// MPRPC 框架的初始化类（单例对象）
class MprpcApplication {
public:
    // 获取单例对象
    static MprpcApplication& GetInstance();

    // 初始化 RPC 框架
    static void Init(int argc, char** argv);

    // 获取配置信息
    static MprpcConfig& GetConfig();

private:
    // 配置内容
    static MprpcConfig m_config;

    // 私有构造函数
    MprpcApplication();

    // 私有析构函数
    ~MprpcApplication();

    // 删除拷贝构造函数
    MprpcApplication(const MprpcApplication&) = delete;

    // 删除赋值运算符
    MprpcApplication& operator=(const MprpcApplication&) = delete;
};