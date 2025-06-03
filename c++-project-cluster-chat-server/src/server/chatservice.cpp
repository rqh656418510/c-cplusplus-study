/**
 * 聊天服务器的业务实现
 */

#include "chatservice.hpp"

#include <muduo/base/Logging.h>

#include <iostream>
#include <vector>

#include "friendmodel.hpp"
#include "offlinemessagemodel.hpp"
#include "public.hpp"
#include "times.hpp"
#include "usermodel.hpp"

using namespace std;
using namespace muduo;

// 构造函数
ChatService::ChatService() {
    // 关联登录业务
    _msgHandlerMap.insert(
        {MsgType::LOGIN_MSG, bind(&ChatService::login, this, placeholders::_1, placeholders::_2, placeholders::_3)});
    // 关联注册业务
    _msgHandlerMap.insert(
        {MsgType::REGISTER_MSG, bind(&ChatService::reg, this, placeholders::_1, placeholders::_2, placeholders::_3)});
    // 关联一对一聊天业务
    _msgHandlerMap.insert({MsgType::SINGLE_CHAT_MSG,
                           bind(&ChatService::singleChat, this, placeholders::_1, placeholders::_2, placeholders::_3)});
    // 关联添加好友业务
    _msgHandlerMap.insert({MsgType::ADD_FRIEND_MSG,
                           bind(&ChatService::addFriend, this, placeholders::_1, placeholders::_2, placeholders::_3)});
    // 关联添加群组业务
    _msgHandlerMap.insert({MsgType::CREATE_GROUP_MSG, bind(&ChatService::createGroup, this, placeholders::_1,
                                                           placeholders::_2, placeholders::_3)});
    // 关联加入群组业务
    _msgHandlerMap.insert({MsgType::JOIN_GROUP_MSG,
                           bind(&ChatService::joinGroup, this, placeholders::_1, placeholders::_2, placeholders::_3)});
    // 关联群聊天业务
    _msgHandlerMap.insert({MsgType::GROUP_CHAT_MSG,
                           bind(&ChatService::groupChat, this, placeholders::_1, placeholders::_2, placeholders::_3)});
    // 关联退出登录业务
    _msgHandlerMap.insert({MsgType::LOGIN_OUT_MSG,
                           bind(&ChatService::loginOut, this, placeholders::_1, placeholders::_2, placeholders::_3)});
}

// 获取单例对象
ChatService* ChatService::instance() {
    // 局部静态变量（线程安全）
    static ChatService instance;
    return &instance;
}

// 获取消息对应的处理器
MsgHandler ChatService::getMsgHandler(int msgType) {
    // 查找消息处理器
    auto it = _msgHandlerMap.find(msgType);
    // 如果消息处理器不存在
    if (it == _msgHandlerMap.end()) {
        // 返回一个默认的消息处理器（空操作）
        return [=](const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time) {
            // 打印日志信息
            LOG_ERROR << "not found message handler by message type " << msgType;
        };
    }
    return _msgHandlerMap[msgType];
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
            response["errNum"] = ErrorCode::REPEAT_LOGIN;
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
            response["errNum"] = ErrorCode::SUCCESS;
            response["userId"] = user.getId();
            response["userName"] = user.getName();
            response["msgType"] = MsgType::LOGIN_MSG_ACK;

            // 查询该用户是否有离线消息
            vector<OfflineMessage> messages = _offflineMessageModel.select(user.getId());
            if (!messages.empty()) {
                // 返回该用户的所有离线消息
                response["offlinemsg"] = messages;
                // 读取该用户的离线消息后，将该用户的离线消息全部删除掉
                _offflineMessageModel.remove(user.getId());
            }

            // 查询该用户的好友列表
            vector<User> friends = _friendModel.select(user.getId());
            if (!friends.empty()) {
                // 返回该用户的好友列表
                response["friends"] = friends;
            }

            // 查询该用户的群组列表
            vector<Group> groups = _groupUserModel.select(user.getId());
            if (!groups.empty()) {
                response["groups"] = groups;
            }

            // 返回数据给客户端
            conn->send(response.dump());
        }
    }
    // 登录失败
    else {
        // 返回数据给客户端
        json response;
        response["errNum"] = ErrorCode::LOGIN_AUTH_FAIL;
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
        response["errNum"] = ErrorCode::REPEAT_REGISTER;
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
        response["errNum"] = ErrorCode::SUCCESS;
        response["userId"] = newUser.getId();
        response["msgType"] = MsgType::REGISTER_MSG_ACK;
        conn->send(response.dump());
    }
    // 插入用户记录失败
    else {
        // 返回数据给客户端
        json response;
        response["errNum"] = ErrorCode::REGISTER_FAIL;
        response["errMsg"] = "用户注册失败";
        response["msgType"] = MsgType::REGISTER_MSG_ACK;
        conn->send(response.dump());
    }
}

// 处理一对一聊天消息
void ChatService::singleChat(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time) {
    // 消息发送者的用户ID
    int fromId = (*data)["fromId"].get<int>();

    // 消息发送者的用户名称
    string fromName = (*data)["fromName"].get<string>();

    // 消息发送者的消息内容
    string fromMsg = (*data)["fromMsg"].get<string>();

    // 消息发送的时间戳
    long fromTimestamp = (*data)["fromTimestamp"].get<long>();

    // 消息接收者的用户ID
    int toId = (*data)["toId"].get<int>();

    // 消息接收者是否在线
    bool toOnline = false;

    // 获取互斥锁
    unique_lock<mutex> lock(_connMapmutex);

    // 获取消息接收者的连接信息
    auto it = _userConnMap.find(toId);
    if (it != _userConnMap.end()) {
        // 记录消息接收者在线
        toOnline = true;
        // 转发消息给消息接收者
        it->second->send((*data).dump());
    }

    // 释放互斥锁
    lock.unlock();

    // 用户不在线，存储离线消息
    if (!toOnline) {
        OfflineMessage msg(toId, (*data).dump(), fromTimestamp);
        // 新增离线消息
        _offflineMessageModel.insert(msg);
    }

    // 返回数据给客户端
    json response;
    response["errNum"] = ErrorCode::SUCCESS;
    response["msgType"] = MsgType::SINGLE_CHAT_MSG_ACK;
    conn->send(response.dump());
}

// 处理添加好友消息
void ChatService::addFriend(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time) {
    // 当前用户的ID
    int userId = (*data)["userId"].get<int>();

    // 好友的用户ID
    int friendId = (*data)["friendId"].get<int>();

    // 控制不能添加自己为好友
    if (userId == friendId) {
        // 返回数据给客户端
        json response;
        response["errNum"] = ErrorCode::ADD_FRIEND_FAIL;
        response["errMsg"] = "不允许添加自己为好友";
        response["msgType"] = MsgType::ADD_FRIEND_MSG_ACK;
        conn->send(response.dump());
        return;
    }

    // 新增好友关系
    _friendModel.insert(userId, friendId);

    // 返回数据给客户端
    json response;
    response["errNum"] = ErrorCode::SUCCESS;
    response["msgType"] = MsgType::ADD_FRIEND_MSG_ACK;
    conn->send(response.dump());
}

// 处理创建群组消息
void ChatService::createGroup(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time) {
    string groupname = (*data)["groupname"].get<string>();
    string groupdesc = (*data)["groupdesc"].get<string>();

    // 当前用户的 ID
    int userid = getCurrUserId(conn);

    // 新增群组
    Group group(groupname, groupdesc);
    bool result = _groupModel.insert(group);

    // 添加群组的创建人信息
    if (result && group.getId() != -1) {
        GroupUser groupUser;
        groupUser.setGroupId(group.getId());
        groupUser.setUserId(userid);
        groupUser.setGroupRole("creator");
        // 新增群组和用户的关联信息
        _groupUserModel.insert(groupUser);
    }

    // 返回数据给客户端
    json response;
    response["errNum"] = ErrorCode::SUCCESS;
    response["msgType"] = MsgType::CREATE_GROUP_MSG_ACK;
    conn->send(response.dump());
}

// 处理加入群组消息
void ChatService::joinGroup(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time) {
    int groupid = (*data)["groupid"].get<int>();

    // 当前用户的 ID
    int userid = getCurrUserId(conn);

    // 新增群组和用户的关联信息
    GroupUser groupUser(groupid, userid, "normal");
    _groupUserModel.insert(groupUser);

    // 返回数据给客户端
    json response;
    response["errNum"] = ErrorCode::SUCCESS;
    response["msgType"] = MsgType::JOIN_GROUP_MSG_ACK;
    conn->send(response.dump());
}

// 处理群聊天消息
void ChatService::groupChat(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time) {
    // 消息发送者的用户ID
    int fromId = (*data)["fromId"].get<int>();

    // 消息发送者的用户名称
    string fromName = (*data)["fromName"].get<string>();

    // 群组的ID
    int groupid = (*data)["groupid"].get<int>();

    // 群组消息的内容
    string groupmsg = (*data)["groupmsg"].get<string>();

    // 当前的时间戳
    long timestamp = getTimestampMs();

    // 当前用户的 ID
    int userid = getCurrUserId(conn);

    // 查询群组内的用户（除了当前用户）
    vector<User> users = _groupUserModel.selectGroupUsers(groupid, userid);

    // 处理群聊消息
    if (!users.empty()) {
        // 获取互斥锁
        unique_lock<mutex> lock;

        // 遍历群组内的用户
        for (User& user : users) {
            // 获取连接信息
            auto it = _userConnMap.find(user.getId());
            if (it != _userConnMap.end()) {
                // 用户在线，转发群聊消息
                (*data)["timestamp"] = timestamp;
                it->second->send((*data).dump());
            } else {
                // 用户不在线，存储离线群聊消息
                OfflineMessage message;
                message.setUserId(user.getId());
                message.setCreateTime(timestamp);
                message.setMessage((*data).dump());
                _offflineMessageModel.insert(message);
            }
        }
    }

    // 返回数据给客户端
    json response;
    response["errNum"] = ErrorCode::SUCCESS;
    response["msgType"] = MsgType::GROUP_CHAT_MSG_ACK;
    conn->send(response.dump());
}

// 处理退出登录消息
void ChatService::loginOut(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time) {
    // 关闭客户端连接
    clientConnClose(conn);

    // 返回数据给客户端
    json response;
    response["errNum"] = ErrorCode::SUCCESS;
    response["msgType"] = MsgType::LOGIN_OUT_MSG_ACK;
    conn->send(response.dump());
}

// 处理用户连接关闭的情况
void ChatService::clientConnClose(const TcpConnectionPtr& conn) {
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

// 获取当前用户的 ID
int ChatService::getCurrUserId(const TcpConnectionPtr& conn) {
    // 当前用户的 ID
    int userid = -1;

    // 获取互斥锁
    unique_lock<mutex> lock(_connMapmutex);

    // 从Map表中删除用户对应的连接信息
    for (auto it = _userConnMap.begin(); it != _userConnMap.end(); ++it) {
        if (it->second == conn) {
            // 记录当前连接对应的用户ID
            userid = it->first;
            break;
        }
    }

    // 释放互斥锁
    lock.unlock();

    return userid;
}

// 处理服务器（Ctrl+C）退出后的业务重置
void ChatService::reset() {
    // 重置所有用户的登录状态
    _userModel.resetState();
}
