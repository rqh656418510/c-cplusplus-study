#include <stdlib.h>

#include "EPollPoller.h"
#include "Logger.h"
#include "Poller.h"

// 创建默认的 I/O 多路复用器
Poller* Poller::newDefaultPoller(EventLoop* loop) {
    if (::getenv("MYMUDUO_USE_POLL")) {
        // 创建 Poll 的实例
        LOG_FATAL("not support poll, only support epoll");
        return nullptr;
    } else {
        // 创建 Epoll 的实例
        return new EPollPoller(loop);
    }
}