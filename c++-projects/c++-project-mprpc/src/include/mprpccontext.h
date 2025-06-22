#pragma once

#include "mprpcchannel.h"
#include "mprpcconfig.h"

// ZooKeeper 节点的路径前缀
const static std::string ZNODE_PATH_PREFIX = "/mprpc/services";

// MPRPC 框架的上下文类（单例对象）
class MprpcContext {
public:
    // 获取单例对象
    static MprpcContext& GetInstance();

    // 初始化 RPC 框架
    static void Init(int argc, char** argv);

    // 获取配置信息
    static MprpcConfig& GetConfig();

private:
    // 配置信息
    static MprpcConfig m_config;

    // 私有构造函数
    MprpcContext();

    // 私有析构函数
    ~MprpcContext();

    // 删除拷贝构造函数
    MprpcContext(const MprpcContext&) = delete;

    // 删除赋值运算符
    MprpcContext& operator=(const MprpcContext&) = delete;
};