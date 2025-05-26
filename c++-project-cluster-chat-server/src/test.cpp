#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <iostream>
#include <string>

#include "muduo_client.h"
#include "muduo_server.h"

using namespace std;

int main() {
    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");

    // 启动服务器
    server.start();

    // 以阻塞方式等待新用户的连接、已连接用户的读写事件等
    loop.loop();

    return 0;
}
