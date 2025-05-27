/**
 * 聊天服务器的业务实现
 */

#include "chatservice.hpp"

#include "public.hpp"

// 获取单例对象
ChatService* ChatService::instance() {
    // 局部静态变量（线程安全）
    static ChatService instance;
    return &instance;
}

// 处理登录业务
void ChatService::login(const TcpConnectionPtr& conn, json& data, Timestamp time) {
}

// 处理注册业务
void ChatService::reg(const TcpConnectionPtr& conn, json& data, Timestamp time) {
}