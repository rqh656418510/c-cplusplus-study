/**
 * MyMuduo 网络库的使用案例
 */

#include <iostream>
#include <string>

#include "EchoServer.h"
#include "EventLoop.h"
#include "InetAddress.h"

// 测试 TCP 服务端
void testEchoServer() {
    // 创建服务端
    EventLoop loop;
    InetAddress addr(6000, "127.0.0.1");
    EchoServer server(&loop, addr, "EchoServer");

    // 启动服务端
    server.start();

    // 以阻塞方式等待新客户端的连接、已连接客户端的读写事件等
    loop.loop();
}

int main() {
    testEchoServer();
    return 0;
}
