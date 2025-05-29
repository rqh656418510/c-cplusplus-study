#ifndef PUBLIC_H
#define PUBLIC_H

/**
 * 公共头文件
 */

// 消息类型
enum MsgType {
    LOGIN_MSG = 1,     // 登录消息
    LOGIN_MSG_ACK,     // 登录响应消息
    REGISTER_MSG,      // 注册消息
    REGISTER_MSG_ACK,  // 注册响应消息
    SINGLE_CHAT_MSG,   // 一对一聊天消息
    GROUP_CHAT_MSG     // 群组聊天消息
};

#endif  // PUBLIC_H