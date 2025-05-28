#ifndef PUBLIC_H
#define PUBLIC_H

/**
 * 公共头文件
 */

// 消息类型
enum MsgType {
    LOGIN_MSG = 1,    // 登录消息
    LOGIN_MSG_ACK,    // 登录响应消息
    REGISTER_MSG,     // 注册消息
    REGISTER_MSG_ACK  // 注册响应消息
};

#endif  // PUBLIC_H