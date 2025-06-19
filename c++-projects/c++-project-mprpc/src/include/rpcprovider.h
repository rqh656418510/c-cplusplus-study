#pragma once

#include <google/protobuf/descriptor.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

#include "google/protobuf/service.h"

// RPC 框架专门提供用来注册 RPC 服务的网络对象类
class RpcProvider {
public:
    // 注册 RPC 服务
    void RegisterService(google::protobuf::Service* service);

    // 启动 RPC 服务节点，开始对外提供 RPC 远程网络调用服务
    void Run();

private:
    // TCP 服务器的事件回环
    muduo::net::EventLoop m_eventloop;

    // RPC 服务信息
    struct ServiceInfo {
        // RPC 服务
        google::protobuf::Service* m_service;
        // RPC 服务拥有的方法
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> m_methodMap;
    };

    // 存储注册成功的 RPC 服务的集合
    std::unordered_map<std::string, ServiceInfo> m_serviceMap;

    // 处理 TCP 连接的创建和断开
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    // 处理已建立 TCP 连接的读写事件（比如接收客户端发送的数据）
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time);

    // 用于序列化 RPC 调用的响应结果和发送网络响应数据
    void SendRpcResponse(const muduo::net::TcpConnectionPtr& conn, google::protobuf::Message* response);
};