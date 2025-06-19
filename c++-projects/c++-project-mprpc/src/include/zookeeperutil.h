#pragma once

#include <semaphore.h>
#include <zookeeper/zookeeper.h>

#include <string>

// ZooKeeper 的客户端封装类
class ZkClient {
public:
    // 构造函数
    ZkClient();

    // 析构函数
    ~ZkClient();

    // 启动 ZK 客户端
    void Start();

    // 在 ZK 服务器上，根据指定的 Path 创建 ZNode 节点
    void Create(const char *path, const char *data, int datalen, int mode = 0);

    // 在 ZK 服务器上，根据指定的 Path 获取 ZNode 节点的值
    std::string GetData(const char *path);

private:
    zhandle_t *m_zhandle;  // ZK 的客户端句柄
};