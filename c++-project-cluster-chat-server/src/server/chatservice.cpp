/**
 * 聊天服务器的业务实现
 */

#include "chatservice.hpp"

#include <muduo/base/Logging.h>

#include <iostream>
#include <vector>

#include "offlinemessagemodel.hpp"
#include "public.hpp"
#include "usermodel.hpp"

using namespace std;
using namespace muduo;

// 构造函数
ChatService::ChatService() {
    // 关联消息ID和消息处理器
    _msgHandlerMap.insert(
        {MsgType::LOGIN_MSG, bind(&ChatService::login, this, placeholders::_1, placeholders::_2, placeholders::_3)});
    _msgHandlerMap.insert(
        {MsgType::REGISTER_MSG, bind(&ChatService::reg, this, placeholders::_1, placeholders::_2, placeholders::_3)});
    _msgHandlerMap.insert({MsgType::SINGLE_CHAT_MSG,
                           bind(&ChatService::singleChat, this, placeholders::_1, placeholders::_2, placeholders::_3)});
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
        return [=](const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time) {
            // 打印日志信息
            LOG_ERROR << "not found message handler by msgid " << msgId;
        };
    }
    return _msgHandlerMap[msgId];
}

// 处理登录业务
void ChatService::login(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time) {
    int id = (*data)["id"].get<int>();
    string password = (*data)["password"].get<string>();

    // 查询用户信息
    User user = _userModel.select(id);

    // 登录成功
    if (user.getId() == id && user.getPassword() == password) {
        // 重复登录
        if (user.getState() == "online") {
            // 返回数据给客户端
            json response;
            response["errNum"] = 2;
            response["errMsg"] = "该账号在其他设备已登录";
            response["msgType"] = MsgType::LOGIN_MSG_ACK;
            conn->send(response.dump());
        }
        // 登录成功
        else {
            // 获取互斥锁
            unique_lock<mutex> lock(_connMapmutex);

            // 存储在线用户的通信连接
            _userConnMap.insert({user.getId(), conn});

            // 释放互斥锁
            lock.unlock();

            // 更新用户登录状态
            user.setState("online");
            _userModel.updateState(user);

            // 返回给客户端的数据
            json response;
            response["errNum"] = 0;
            response["userId"] = user.getId();
            response["userName"] = user.getName();
            response["msgType"] = MsgType::LOGIN_MSG_ACK;

            // 查询该用户是否有离线消息
            vector<OfflineMessage> messages = _offflineMessageModel.select(user.getId());
            if (!messages.empty()) {
                // 返回所有离线消息给该用户
                response["offlinemsg"] = messages;
                // 读取该用户的离线消息后，将该用户的离线消息全部删除掉
                _offflineMessageModel.remove(user.getId());
            }

            conn->send(response.dump());
        }
    }
    // 登录失败
    else {
        // 返回数据给客户端
        json response;
        response["errNum"] = 2;
        response["errMsg"] = "用户名或密码不正确";
        response["msgType"] = MsgType::LOGIN_MSG_ACK;
        conn->send(response.dump());
    }
}

// 处理注册业务
void ChatService::reg(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time) {
    // 创建用户对象
    string name = (*data)["name"].get<string>();
    string password = (*data)["password"].get<string>();

    // 查询用户名是否已被注册
    User oldUser = _userModel.selectByName(name);
    if (oldUser.getId() != -1) {
        // 返回数据给客户端
        json response;
        response["errNum"] = 1;
        response["errMsg"] = "用户名已被注册";
        response["msgType"] = MsgType::REGISTER_MSG_ACK;
        conn->send(response.dump());
        return;
    }

    // 插入用户记录
    User newUser(name, password);
    bool result = _userModel.insert(newUser);

    // 插入用户记录成功
    if (result) {
        // 返回数据给客户端
        json response;
        response["errNum"] = 0;
        response["userId"] = newUser.getId();
        response["msgType"] = MsgType::REGISTER_MSG_ACK;
        conn->send(response.dump());
    }
    // 插入用户记录失败
    else {
        // 返回数据给客户端
        json response;
        response["errNum"] = 1;
        response["msgType"] = MsgType::REGISTER_MSG_ACK;
        conn->send(response.dump());
    }
}

// 处理一对一聊天消息
void ChatService::singleChat(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time) {
    // 消息发送者的用户ID
    int fromId = (*data)["fromId"].get<int>();

    // 消息发送者的消息内容
    string fromMsg = (*data)["fromMsg"].get<string>();

    // 消息接收者的用户ID
    int toId = (*data)["toId"].get<int>();

    // 消息接收者是否在线
    bool toOnline = false;

    // 获取互斥锁
    unique_lock<mutex> lock(_connMapmutex);

    // 获取消息接收者的连接信息
    auto it = _userConnMap.find(toId);
    if (it != _userConnMap.end()) {
        // 用户在线，发送消息给消息接收者
        toOnline = true;
        it->second->send((*data).dump());
    }

    // 释放互斥锁
    lock.unlock();

    // 用户不在线，存储离线消息
    if (!toOnline) {
        OfflineMessage msg(toId, (*data).dump(), timestamp());
        // 新增离线消息
        _offflineMessageModel.insert(msg);
    }
}

// 处理用户连接异常关闭的情况
void ChatService::clientCloseExcetpion(const TcpConnectionPtr& conn) {
    // 用户信息
    User user;

    // 获取互斥锁
    unique_lock<mutex> lock(_connMapmutex);

    // 从Map表中删除用户对应的连接信息
    for (auto it = _userConnMap.begin(); it != _userConnMap.end(); ++it) {
        if (it->second == conn) {
            // 记录用户ID
            user.setId(it->first);
            // 移除连接信息
            _userConnMap.erase(it->first);
            break;
        }
    }

    // 释放互斥锁
    lock.unlock();

    // 更新用户的登录状态
    if (user.getId() != -1) {
        user.setState("offline");
        _userModel.updateState(user);
    }
}

// 处理服务器（Ctrl+C）退出后的业务重置
void ChatService::reset() {
    // 重置所有用户的登录状态
    _userModel.resetState();
}