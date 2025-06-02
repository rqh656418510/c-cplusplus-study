/**
 * 聊天服务器的实现
 */

#include "chatserver.hpp"

#include <muduo/base/Logging.h>

#include <iostream>
#include <string>

#include "chatservice.hpp"
#include "json.hpp"
#include "public.hpp"

using namespace std;
using namespace muduo;

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
    if (!conn->connected()) {
        // 处理用户连接关闭的情况
        ChatService::instance()->clientConnClose(conn);
        // 断开连接（释放资源）
        conn->shutdown();
    }
}

// 处理用户读写事件（比如接收客户端发送的数据）
void ChatServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
    // 获取客户端发送的数据
    string message = buf->retrieveAllAsString();

    // 打印日志信息
    LOG_DEBUG << "server received message : " << message;

    // JSON 字符串反序列化
    json jsonObj = json::parse(message);

    // 非法消息直接忽略处理
    if (!jsonObj.contains("msgType")) {
        // 返回数据给客户端
        json response;
        response["errNum"] = ErrorCode::INVALID_MESSAGE_TYPE;
        response["errMsg"] = "消息类型无效";
        conn->send(response.dump());
        return;
    }

    // 消息类型
    int msgType = jsonObj["msgType"].get<int>();

    // 统一验证用户是否已登录
    if (msgType != MsgType::LOGIN_MSG && msgType != MsgType::REGISTER_MSG) {
        int userid = ChatService::instance()->getCurrUserId(conn);
        if (userid == -1) {
            // 返回数据给客户端
            json response;
            response["errNum"] = ErrorCode::REQUIRE_LOGIN;
            response["errMsg"] = "请登录客户端";
            conn->send(response.dump());
            return;
        }
    }

    // 获取消息处理器
    auto msgHandler = ChatService::instance()->getMsgHandler(msgType);

    // 调用消息处理器，执行相应的业务处理
    msgHandler(conn, make_shared<json>(jsonObj), time);
}