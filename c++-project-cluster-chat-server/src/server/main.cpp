#include <muduo/base/Logging.h>
#include <signal.h>

#include <iostream>

#include "chatserver.hpp"
#include "chatservice.hpp"

using namespace std;
using namespace muduo;

// 处理服务器（Ctrl+C）退出后的业务重置
void resetHandler(int signal) {
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        cerr << "command invalid, example: ./chat_server 127.0.0.1 6000" << endl;
        exit(-1);
    }

    // 解析通过命令行参数传递的IP和端口号
    char *ip = argv[1];
    uint16_t port = atoi(argv[2]);

    // 设置日志级别为 DEBUG
    Logger::setLogLevel(Logger::DEBUG);

    // 打印日志信息
    LOG_INFO << "chat server start ...";

    // 注册中断信号（SIGINT）的处理器
    signal(SIGINT, resetHandler);

    // 定义聊天服务器
    EventLoop loop;
    InetAddress address(ip, port);
    ChatServer server(&loop, address, "ChatServer");

    // 启动聊天服务器
    server.start();

    // 以阻塞的方式等待新客户端的连接、已连接客户端的读写事件等
    loop.loop();

    return 0;
}