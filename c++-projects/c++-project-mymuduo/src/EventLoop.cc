#include "EventLoop.h"

#include "CurrentThread.h"

// 获取 Poller 返回发生事件的时间点
Timestamp EventLoop::pollReturnTime() const {
    return pollReturnTime_;
}

// 判断当前线程是否是 EventLoop 所在线程
bool EventLoop::isInLoopThread() const {
    return threadId_ == CurrentThread::tid();
}