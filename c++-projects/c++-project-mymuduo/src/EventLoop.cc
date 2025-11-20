#include "EventLoop.h"

#include <sys/eventfd.h>
#include <unistd.h>

#include "Channel.h"
#include "CurrentThread.h"
#include "Logger.h"
#include "Poller.h"

// 定义线程局部变量（thread-local），用于防止一个线程创建多个 EventLoop
__thread EventLoop* t_loopInThisThread = nullptr;

// 定义 Poller（I/O 多路复用器）默认的超时时间
const int kPollTimeMs = 10000;

// 创建 wakeupFd，用来 Notify（唤醒）SubReactor 处理新来的 Channel
int createEventFd() {
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0) {
        LOG_FATAL("%s => eventfd error:%d \n", __PRETTY_FUNCTION__, errno);
    }
    return evtfd;
}

// 构造函数
EventLoop::EventLoop()
    : looping_(false),
      quit_(false),
      callingPendingFunctors_(false),
      threadId_(CurrentThread::tid()),
      poller_(Poller::newDefaultPoller(this)),
      wakeupFd_(createEventFd()),
      wakeupChannel_(new Channel(this, wakeupFd_)) {
    // 打印日志信息
    LOG_DEBUG("%s => EventLoop created %p in thread %d \n", __PRETTY_FUNCTION__, this, threadId_);

    // 防止一个线程创建多个 EventLoop
    if (t_loopInThisThread) {
        LOG_FATAL("%s => Another EventLoop existed in this thread %d \n", __PRETTY_FUNCTION__, threadId_);
    } else {
        // 将当前 EventLoop 对象赋值给线程局部变量
        t_loopInThisThread = this;
    }

    // 设置 Wakeup Channel 的读事件回调函数
    wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));

    // 启用 Wakeup Channel 的读事件监听
    wakeupChannel_->enableReading();
}

// 析构函数
EventLoop::~EventLoop() {
    LOG_DEBUG("%s => EventLoop %p of thread %d destructs in thread \n", __PRETTY_FUNCTION__, this,
              CurrentThread::tid());
    // 关闭 Wakeup Channel
    wakeupChannel_->disableAll();
    // 移除 Wakeup Channel
    wakeupChannel_->remove();
    // 关闭 wakeupFd_
    ::close(wakeupFd_);
    // 重置线程局部变量
    t_loopInThisThread = nullptr;
}

// 开启事件循环
void EventLoop::loop() {
    // 标记事件循环开始
    looping_ = true;

    // 标记退出事件循环的状态
    quit_ = false;

    // 打印日志信息
    LOG_DEBUG("%s => EventLoop %p start looping \n", __PRETTY_FUNCTION__, this);

    while (!quit_) {
        activeChannels_.clear();
        // Poller 监听有哪些 Channel 发生了事件，然后上报给 EventLoop，通知 Channel 处理相应的事件
        pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);
        for (Channel* channel : activeChannels_) {
            channel->handleEvent(pollReturnTime_);
        }
        // 执行当前 EventLoop 需要处理的回调操作
        doPendingFunctors();
    }

    // 打印日志信息
    LOG_DEBUG("%s => EventLoop %p stop looping \n", __PRETTY_FUNCTION__, this);

    // 标记事件循环结束
    looping_ = false;
}

// 执行所有回调操作
void EventLoop::doPendingFunctors() {
}

// 退出事件循环
void EventLoop::quit() {
    // 标记退出事件循环的状态
    quit_ = true;

    // 如果不是在当前 EventLoop 所在线程上调用的 quit() 方法，则需要唤醒 EventLoop 所在线程
    if (!isInLoopThread()) {
        wakeup();
    }
}

// 唤醒 EventLoop 所在线程
void EventLoop::wakeup() {
}

// 处理 Wakeup Channel 的读事件
void EventLoop::handleRead() {
    uint64_t one = 1;
    ssize_t n = ::read(wakeupFd_, &one, sizeof one);
    if (n != sizeof one) {
        LOG_ERROR("%s reads %zd bytes instead of 8 \n", __PRETTY_FUNCTION__, n);
    }
}

// 获取 Poller 返回发生事件的时间点
Timestamp EventLoop::pollReturnTime() const {
    return pollReturnTime_;
}

// 判断当前线程是否是 EventLoop 所在线程
bool EventLoop::isInLoopThread() const {
    return threadId_ == CurrentThread::tid();
}