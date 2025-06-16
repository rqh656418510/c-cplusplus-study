#pragma once

#include <muduo/base/Timestamp.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>

#include <memory>

#include "google/protobuf/service.h"

// RPC 框架专门提供用来发布 RPC 服务的网络对象类
class RpcProvider {
public:
    // 发布 RPC 服务
    void NotifyService(google::protobuf::Service* service);

    // 启动 RPC 服务节点，开始对外提供 RPC 远程网络调用服务
    void Run();

private:
    // TCP 服务器的事件回环
    muduo::net::EventLoop m_eventloop;

    // 处理 TCP 连接的创建和断开
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    // 处理已建立 TCP 连接的读写事件（比如接收客户端发送的数据）
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time);
};