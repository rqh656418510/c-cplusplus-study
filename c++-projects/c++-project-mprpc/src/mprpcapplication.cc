#include "mprpcapplication.h"

#include <unistd.h>

#include <iostream>
#include <string>

// 初始化类静态成员变量
MprpcConfig MprpcApplication::m_config;

// 构造函数
MprpcApplication::MprpcApplication() {
}

// 析构函数
MprpcApplication::~MprpcApplication() {
}

// 获取单例对象
MprpcApplication& MprpcApplication::GetInstance() {
    // 局部静态变量（线程安全）
    static MprpcApplication singleton;
    return singleton;
}

// 打印命令帮助内容
void ShowArgsHelp() {
    std::cout << "format: command -i <configfile>" << std::endl;
}

// 初始化 RPC 框架
void MprpcApplication::Init(int argc, char** argv) {
    // 校验命令行参数
    if (argc < 2) {
        ShowArgsHelp();
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
                std::cout << "invalid args!" << std::endl;
                ShowArgsHelp();
                exit(EXIT_FAILURE);
            case ':':
                std::cout << "need <configfile>" << std::endl;
                ShowArgsHelp();
                exit(EXIT_FAILURE);
            default:
                break;
        }
    }

    std::cout << "loading rpc config file: " << config_file << std::endl;

    // 开始读取配置文件
    m_config.LoadConfigFile(config_file.c_str());
}