#pragma once

#include "google/protobuf/service.h"

// RPC 框架专门提供用来发布 RPC 服务的网络对象类
class RpcProvider {
public:
    // 发布 RPC 服务
    void NotifyService(google::protobuf::Service* service);

    // 启动 RPC 服务节点，开始对外提供 RPC 远程网络调用服务
    void Run();
};