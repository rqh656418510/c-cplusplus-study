#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

using namespace muduo;
using namespace muduo::net;

// 聊天服务器类
class ChatServer {
public:
    // 构造函数
    ChatServer(EventLoop* loop, const InetAddress& listenAddr, const string& nameArg);

    // 析构函数
    ~ChatServer();

    // 启动服务器
    void start();

private:
    // 处理用户的连接创建和断开
    void onConnection(const TcpConnectionPtr& conn);

    // 处理用户读写事件（比如接收客户端发送的数据）
    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);

    TcpServer _server;  // TCP 服务器对象
    EventLoop* _loop;   // 指向事件回环的指针
};

#endif  // CHATSERVER_H