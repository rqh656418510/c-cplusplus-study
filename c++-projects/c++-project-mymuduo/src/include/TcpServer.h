#pragma once

#include <iostream>

#include "noncopyable.h"

// 类的前向声明
class Acceptor;
class EventLoop;
class EventLoopThreadPool;

// TCP 服务器类
class TcpServer : noncopyable {
public:
    // 构造函数
    TcpServer();

    // 析构函数
    ~TcpServer();
};