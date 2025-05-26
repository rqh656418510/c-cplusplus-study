#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <iostream>
#include <string>
#include <thread>

#include "muduo_client.h"
#include "muduo_log.h"
#include "muduo_pool.h"
#include "muduo_server.h"

// 初始化服务器
void initServer() {
    // 创建服务器
    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");

    // 启动服务器
    server.start();

    // 以阻塞方式等待新用户的连接、已连接用户的读写事件等
    loop.loop();
}

// 初始化客户端
void initClient() {
    ////////////////////////////// 使用 Muduo 实现 TCP 服务器和客户端 //////////////////////////////

    // 创建客户端
    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr("127.0.0.1", 6000);
    ChatClient client(&loop, addr, "ChatClient");

    // 连接服务器
    client.connect();

    // 以阻塞方式等待服务器发送的数据
    loop.loop();
}

int main() {
    // 启动服务器线程
    std::thread serverThread(initServer);
    serverThread.detach();

    // 等待一会，让服务器线程先启动
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // 启动客户端线程
    std::thread clientThread(initClient);
    clientThread.detach();

    ////////////////////////////// 使用 Muduo 线程池 //////////////////////////////

    runSumTasks();

    ////////////////////////////// 使用 Muduo 日志模块 //////////////////////////////

    outlog();

    // 阻塞等待用户按下任意键，然后结束程序运行
    char c = getchar();

    return 0;
}