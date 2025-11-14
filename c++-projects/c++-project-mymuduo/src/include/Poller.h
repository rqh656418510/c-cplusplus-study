#pragma once

#include <iostream>

#include "noncopyable.h"

// 类前置声明
class Channel;

/**
 * 基于 epoll 实现的 I/O 多路复用器
 */
class Poller : noncopyable {};