#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Logger.h"

// 创建非阻塞的 Socket
int createNonblockingSocket();

// 获取 Socket 错误码
int getSocketError(int sockfd);

// 判断是否为自连接
bool isSelfConnect(int sockfd);

// 获取本端地址
sockaddr_in getLocalAddr(int sockfd);

// 获取对端地址
sockaddr_in getPeerAddr(int sockfd);
