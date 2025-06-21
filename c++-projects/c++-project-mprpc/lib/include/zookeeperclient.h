#pragma once

#include <semaphore.h>
#include <zookeeper/zookeeper.h>

#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "logger.h"
#include "mprpcapplication.h"

// ZNode 节点的状态
enum ZNodeStatus {
    EXIST,     // 已存在
    NOTEXIST,  // 不存在
    UNKNOWN    // 未知状态
};

// ZooKeeper 客户端的封装类
class ZkClient {
public:
    // 构造函数
    ZkClient();

    // 析构函数
    ~ZkClient();

    // 启动 ZK 客户端
    bool Start(const std::string &host, const int port);

    // 在 ZK 服务器上，根据指定的 Path 创建 ZNode 节点
    std::string Create(const char *path, const char *data, int datalen = 0, int mode = ZOO_PERSISTENT);

    // 在 ZK 服务器上，根据指定的 Path 递归创建 ZNode 节点
    std::string CreateRecursive(const char *path, const char *data, int datalen = 0, int mode = ZOO_PERSISTENT);

    // 在 ZK 服务器上，根据指定的 Path 获取子节点列表
    std::vector<std::string> GetChildren(const char *path);

    // 在 ZK 服务器上，根据指定的 Path 获取 ZNode 节点的数据
    std::string GetData(const char *path);

    // 在 ZK 服务器上，根据指定的 Path 获取 ZNode 节点的状态
    Stat GetStat(const char *path);

    // 在 ZK 服务器上，根据指定的 Path 判断 ZNode 节点是否存在
    ZNodeStatus Exist(const char *path);

private:
    zhandle_t *m_zhandle;  // ZK 的客户端句柄

    // 检查节点路径是否合法
    bool checkPath(const char *path);
};