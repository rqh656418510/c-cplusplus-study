#include <muduo/base/Logging.h>

#include <iostream>

#include "chatserver.hpp"

using namespace std;
using namespace muduo;

int main() {
    // 设置日志级别为 DEBUG
    Logger::setLogLevel(Logger::DEBUG);

    // 打印日志信息
    LOG_INFO << "chat server start ...";

    // 定义聊天服务器
    EventLoop loop;
    InetAddress address("127.0.0.1", 6000);
    ChatServer server(&loop, address, "ChatServer");

    // 启动聊天服务器
    server.start();

    // 以阻塞的方式等待新客户端的连接、已连接客户端的读写事件等
    loop.loop();

    char c = getchar();

    return 0;
}