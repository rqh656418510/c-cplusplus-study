#pragma once

#include <iostream>

#include "noncopyable.h"

// TCP 服务器
class TcpServer : noncopyable {
public:
    // 构造函数
    TcpServer();

    // 析构函数
    ~TcpServer();
};