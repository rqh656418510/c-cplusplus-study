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

// 创建 wakeupFd，用于线程间的事件通知（notify）
int createEventFd() {
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0) {
        LOG_FATAL("func=%s => eventfd error:%d \n", __PRETTY_FUNCTION__, errno);
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
      wakeupChannel_(new Channel(this, wakeupFd_)),
      currentActiveChannel_(nullptr) {
    // 打印日志信息
    LOG_DEBUG("func=%s => EventLoop created %p in thread %d \n", __PRETTY_FUNCTION__, this, threadId_);

    // 防止一个线程创建多个 EventLoop
    if (t_loopInThisThread) {
        LOG_FATAL("func=%s => Another EventLoop existed in this thread %d \n", __PRETTY_FUNCTION__, threadId_);
    } else {
        // 将当前 EventLoop 对象赋值给线程局部变量
        t_loopInThisThread = this;
    }

    // 设置 wakeupChannel_ 的读事件回调函数
    wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));

    // 启用 wakeupChannel_ 的读事件监听
    wakeupChannel_->enableReading();
}

// 析构函数
EventLoop::~EventLoop() {
}

// 处理唤醒事件
void EventLoop::handleRead() {
    uint64_t one = 1;
    ssize_t n = ::read(wakeupFd_, &one, sizeof one);
    if (n != sizeof one) {
        LOG_ERROR("func=%s reads %zd bytes instead of 8 \n", __PRETTY_FUNCTION__, n);
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