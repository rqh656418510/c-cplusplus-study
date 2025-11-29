/**
 * MyMuduo 网络库的使用案例
 *
 * Linux 上运行程序：./bin/mymuduo_example
 */

#include <chrono>
#include <iostream>
#include <thread>

#include "ChatClient.h"
#include "ChatServer.h"
#include "Logger.h"

// 启动聊天服务器
void startChatServer() {
    // 创建服务器
    EventLoop loop;
    InetAddress addr(6000, "127.0.0.1");
    ChatServer server(&loop, addr, "ChatServer");

    // 启动服务器
    server.start();

    // 以阻塞方式等待新客户端的连接、已连接客户端的读写事件等
    loop.loop();
}

// 启动聊天客户端
void startChatClient() {
    // 创建客户端
    EventLoop loop;
    InetAddress addr(6000, "127.0.0.1");
    ChatClient client(&loop, addr, "ChatClient");

    // 连接服务器
    client.connect();

    // 以阻塞方式等待服务器发送过来的数据
    loop.loop();
}

int main() {
    // 设置日志级别
    Logger::instance().setLogLevel(LogLevel::INFO);

    // 在独立的线程上启动聊天服务器
    std::thread serverThread([]() { startChatServer(); });
    serverThread.detach();

    // 等待一段时间，让聊天服务器先启动（可选，因为聊天客户端会自动重连）
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    // 在独立的线程上启动聊天客户端
    std::thread clientThrad([]() { startChatClient(); });
    clientThrad.detach();

    // 阻塞等待用户输入，然后终止程序
    getchar();

    return 0;
}