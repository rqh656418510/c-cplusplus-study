#ifndef PUBLIC_H
#define PUBLIC_H

/**
 * 公共头文件
 */

// 错误编码
enum ErrorCode {
    SUCCESS = 0,           // 请求处理成功
    REGISTER_FAIL,         // 注册失败
    REPEAT_REGISTER,       // 用户名已被注册
    LOGIN_AUTH_FAIL,       // 用户名或密码不正确
    REPEAT_LOGIN,          // 账号在其他设备已登录
    REQUIRE_LOGIN,         // 当前用户未登录
    ADD_FRIEND_FAIL,       // 添加好友失败
    JOIN_GROUP_FAIL,       // 加入群组失败
    INVALID_MESSAGE_TYPE,  // 消息类型无效
};

// 消息类型
enum MsgType {
    LOGIN_MSG = 1,         // 登录消息
    LOGIN_MSG_ACK,         // 登录响应消息
    REGISTER_MSG,          // 注册消息
    REGISTER_MSG_ACK,      // 注册响应消息
    SINGLE_CHAT_MSG,       // 一对一聊天消息
    SINGLE_CHAT_MSG_ACK,   // 一对一聊天响应消息
    ADD_FRIEND_MSG,        // 添加好友消息
    ADD_FRIEND_MSG_ACK,    // 添加好友响应消息
    CREATE_GROUP_MSG,      // 创建群组消息
    CREATE_GROUP_MSG_ACK,  // 创建群组响应消息
    JOIN_GROUP_MSG,        // 加入群组消息
    JOIN_GROUP_MSG_ACK,    // 加入群组响应消息
    GROUP_CHAT_MSG,        // 群聊天消息
    GROUP_CHAT_MSG_ACK,    // 群聊天响应消息
    LOGIN_OUT_MSG,         // 退出登录消息
    LOGIN_OUT_MSG_ACK,     // 退出登录响应消息
};

#endif  // PUBLIC_H