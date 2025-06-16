#include "rpcprovider.h"

#include <functional>
#include <iostream>
#include <string>

#include "mprpcapplication.h"

// 发布 RPC 服务
void RpcProvider::NotifyService(google::protobuf::Service* service) {
}

// 启动 RPC 服务节点，开始对外提供 RPC 远程网络调用服务
void RpcProvider::Run() {
    // 创建 TCP 服务器
    std::string ip = MprpcApplication::GetInstance().GetConfig().Load("rpc-server-ip");
    std::string port = MprpcApplication::GetInstance().GetConfig().Load("rpc-server-port");
    muduo::net::InetAddress address(ip, atoi(port.c_str()));
    muduo::net::TcpServer tcpServer(&m_eventloop, address, "RpcProvider");

    // 设置 TCP 连接创建和断开的回调
    tcpServer.setConnectionCallback(bind(&RpcProvider::onConnection, this, std::placeholders::_1));

    // 设置已建立 TCP 连接读写事件的回调
    tcpServer.setMessageCallback(
        bind(&RpcProvider::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置 EventLoop 的线程数量（比如：1 个 I/O 线程，3 个 Worker 线程）
    tcpServer.setThreadNum(4);

    // 打印日志信息
    std::cout << "RpcProvider start service at " << ip << ":" << port << std::endl;

    // 启动 TCP 服务器
    tcpServer.start();

    // 以阻塞方式等待新客户端的连接、已连接客户端的读写事件等
    m_eventloop.loop();
}

// 处理 TCP 连接的创建和断开
void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr& conn) {
}

// 处理 TCP 连接的读写事件（比如接收客户端发送的数据）
void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time) {
}