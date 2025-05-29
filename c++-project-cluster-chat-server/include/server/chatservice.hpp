#ifndef CHATSERVICE_H
#define CHATSERVICE_H

/**
 * 聊天服务器的业务头文件
 */

#include <muduo/net/TcpConnection.h>

#include <functional>
#include <iostream>
#include <unordered_map>

#include "json.hpp"
#include "usermodel.hpp"

using namespace std;
using namespace muduo;
using namespace muduo::net;

// 类型重定义
using json = nlohmann::json;

// 处理消息的回调类型（使用智能指针是为了兼容低版本的G++编译器）
using MsgHandler = function<void(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time)>;

// 聊天服务器的业务类（单例对象）
class ChatService {
public:
    // 获取单例对象
    static ChatService* instance();

    // 处理登录业务
    void login(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time);

    // 处理注册业务
    void reg(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time);

    // 获取消息对应的处理器
    MsgHandler getMsgHandler(int msgId);

private:
    // 私有构造函数
    ChatService();

    // 删除拷贝构造函数
    ChatService(const ChatService&) = delete;

    // 删除赋值运算符
    ChatService& operator=(const ChatService&) = delete;

    // 关联消息ID和消息处理器
    unordered_map<int, MsgHandler> _msgHandlerMap;

    // User 表的数据操作对象
    UserModel _userModel;
};

#endif  // CHATSERVICE_H
