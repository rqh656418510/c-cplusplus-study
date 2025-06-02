#ifndef CHATSERVICE_H
#define CHATSERVICE_H

/**
 * 聊天服务器的业务头文件
 */

#include <muduo/net/TcpConnection.h>

#include <functional>
#include <iostream>
#include <mutex>
#include <unordered_map>

#include "friendmodel.hpp"
#include "groupmodel.hpp"
#include "groupusermodel.hpp"
#include "json.hpp"
#include "offlinemessagemodel.hpp"
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

    // 处理一对一聊天消息
    void singleChat(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time);

    // 处理添加好友消息
    void addFriend(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time);

    // 处理创建群组消息
    void createGroup(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time);

    // 处理加入群组消息
    void joinGroup(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time);

    // 处理群聊天消息
    void groupChat(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time);

    // 处理退出登录消息
    void loginOut(const TcpConnectionPtr& conn, const shared_ptr<json>& data, Timestamp time);

    // 获取消息对应的处理器
    MsgHandler getMsgHandler(int msgType);

    // 处理用户连接异常关闭的情况
    void clientCloseExcetpion(const TcpConnectionPtr& conn);

    // 获取当前用户的 ID
    int getCurrUserId(const TcpConnectionPtr& conn);

    // 处理服务器（Ctrl+C）退出后的业务重置
    void reset();

private:
    // 私有构造函数
    ChatService();

    // 删除拷贝构造函数
    ChatService(const ChatService&) = delete;

    // 删除赋值运算符
    ChatService& operator=(const ChatService&) = delete;

    // 关联消息ID和消息处理器（用于解耦业务代码）
    unordered_map<int, MsgHandler> _msgHandlerMap;

    // 存储在线用户的通信连接（操作时必须自行保证线程安全）
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    // 互斥锁，保证 _userConnMap 的线程安全
    mutex _connMapmutex;

    // User 表的数据操作对象
    UserModel _userModel;

    // OfflineMessage 表的数据操作对象
    OfflineMessageModel _offflineMessageModel;

    // Friend 表的数据操作对象
    FriendModel _friendModel;

    // Group 表的数据操作对象
    GroupModel _groupModel;

    // GroupUser 表的数据操作对象
    GroupUserModel _groupUserModel;
};

#endif  // CHATSERVICE_H