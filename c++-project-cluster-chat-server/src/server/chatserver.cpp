/**
 * 聊天服务器的实现
 */

#include "chatserver.hpp"

#include <iostream>
#include <string>

#include "json.hpp"

using namespace std;

// 类型重定义
using json = nlohmann::json;

// 构造函数
ChatServer::ChatServer(EventLoop* loop, const InetAddress& listenAddr, const string& nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop) {
    // 设置服务端注册用户连接的创建和断开回调
    _server.setConnectionCallback(bind(&ChatServer::onConnection, this, placeholders::_1));

    // 设置服务端注册用户读写事件的回调
    _server.setMessageCallback(
        bind(&ChatServer::onMessage, this, placeholders::_1, placeholders::_2, placeholders::_3));

    // 设置EventLoop的线程数量（比如：1个I/O线程，3个Worker线程）
    _server.setThreadNum(4);
}

// 析构函数
ChatServer::~ChatServer() {
}

// 启动服务器
void ChatServer::start() {
    // 开启事件循环处理
    _server.start();
}

// 处理用户的连接创建和断开
void ChatServer::onConnection(const TcpConnectionPtr& conn) {
    // 断开连接（释放资源）
    if (!conn->connected()) {
        conn->shutdown();
    }
}

// 处理用户读写事件（比如接收客户端发送的数据）
void ChatServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
    // 获取客户端发送的数据
    string message = buf->retrieveAllAsString();

    // JSON 字符串反序列化
    json jsonObj = json::parse(message);

    cout << "server receive message: " << message << endl;
}