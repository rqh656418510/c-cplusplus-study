/**
 * 聊天服务器的业务实现
 */

#include "chatservice.hpp"

#include <muduo/base/Logging.h>

#include <iostream>

#include "public.hpp"

using namespace std;
using namespace muduo;

// 构造函数
ChatService::ChatService() {
    // 关联消息ID和消息处理器
    _msgHandlerMap.insert(
        {MsgType::LOGIN_MSG, bind(&ChatService::login, this, placeholders::_1, placeholders::_2, placeholders::_3)});
    _msgHandlerMap.insert(
        {MsgType::REGISTER_MSG, bind(&ChatService::reg, this, placeholders::_1, placeholders::_2, placeholders::_3)});
}

// 获取单例对象
ChatService* ChatService::instance() {
    // 局部静态变量（线程安全）
    static ChatService instance;
    return &instance;
}

// 获取消息对应的处理器
MsgHandler ChatService::getMsgHandler(int msgId) {
    // 查找消息处理器
    auto it = _msgHandlerMap.find(msgId);
    // 如果消息处理器不存在
    if (it == _msgHandlerMap.end()) {
        // 返回一个默认的消息处理器（空操作）
        return [=](const TcpConnectionPtr& conn, const json& data, Timestamp time) {
            // 打印日志信息
            LOG_ERROR << "not found msg handler by msgid " << msgId;
        };
    }
    return _msgHandlerMap[msgId];
}

// 处理登录业务
void ChatService::login(const TcpConnectionPtr& conn, const json& data, Timestamp time) {
    LOG_INFO << "execute login service";
}

// 处理注册业务
void ChatService::reg(const TcpConnectionPtr& conn, const json& data, Timestamp time) {
    LOG_INFO << "execute register service";
}