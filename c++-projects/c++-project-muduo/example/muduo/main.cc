/**
 * Muduo 官方网络库的使用案例
 */

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <iostream>
#include <string>
#include <thread>

#include "chat_client.h"
#include "chat_server.h"
#include "multi_thread_counter.h"

// 测试TCP服务端
void testChatServer() {
    // 创建服务端
    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");

    // 启动服务端
    server.start();

    // 以阻塞方式等待新客户端的连接、已连接客户端的读写事件等
    loop.loop();
}

// 测试TCP客户端
void testChatClient() {
    // 创建客户端
    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr("127.0.0.1", 7000);
    ChatClient client(&loop, addr, "ChatClient");

    // 连接服务端
    client.connect();

    // 以阻塞方式等待服务端发送的数据
    loop.loop();
}

// 测试线程池
void testThreadPool() {
    int threadNumber = 8;
    ULong countRange = 100000000;
    // 执行多线程计算
    ULong totalSum = MultiThreadCounter::count(threadNumber, countRange);
    // 输出计算结果
    std::cout << "1 + 2 + ... + " << countRange << " = " << totalSum << std::endl;
}

int main() {
    testChatServer();
    // testChatClient();
    // testThreadPool();
    return 0;
}
