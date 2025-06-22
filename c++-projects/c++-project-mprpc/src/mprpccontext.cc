#include "mprpccontext.h"

#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "logger.h"

// 初始化类静态成员变量
MprpcConfig MprpcContext::m_config;

// 构造函数
MprpcContext::MprpcContext() {
}

// 析构函数
MprpcContext::~MprpcContext() {
}

// 获取单例对象
MprpcContext& MprpcContext::GetInstance() {
    // 局部静态变量（线程安全）
    static MprpcContext singleton;
    return singleton;
}

// 打印命令帮助内容
void ShowArgsHelp() {
    std::cout << "format: command -i <configfile>" << std::endl;
}

// 初始化 RPC 框架
void MprpcContext::Init(int argc, char** argv) {
    // 校验命令行参数
    if (argc < 2) {
        // 打印命令帮助内容
        ShowArgsHelp();
        // 退出程序
        exit(EXIT_FAILURE);
    }

    // 从命令行获取配置文件的路径
    int c = 0;
    std::string config_file;
    while ((c = getopt(argc, argv, "i:")) != -1) {
        switch (c) {
            case 'i':
                config_file = optarg;
                break;
            case '?':
                std::cout << "invalid command args!" << std::endl;
                // 打印命令帮助内容
                ShowArgsHelp();
                // 退出程序
                exit(EXIT_FAILURE);
            case ':':
                std::cout << "need <configfile>" << std::endl;
                // 打印命令帮助内容
                ShowArgsHelp();
                // 退出程序
                exit(EXIT_FAILURE);
            default:
                break;
        }
    }

    // 打印日志信息
    LOG_DEBUG("loading rpc config file %s", config_file.c_str());

    // 读取配置文件内容
    m_config.LoadConfigFile(config_file.c_str());
}

// 获取配置信息
MprpcConfig& MprpcContext::GetConfig() {
    return m_config;
}