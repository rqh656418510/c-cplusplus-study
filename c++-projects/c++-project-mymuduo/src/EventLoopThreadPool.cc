#include "EventLoopThreadPool.h"

#include "EventLoopThread.h"

// 构造函数
EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop, const std::string& nameArg)
    : baseLoop_(baseLoop), name_(nameArg), started_(false), numThreads_(0), next_(0) {
}

// 析构函数
EventLoopThreadPool::~EventLoopThreadPool() {
    // 析构时不需要删除 loop，因为它是栈变量
}

// 设置线程池的线程数量
void EventLoopThreadPool::setThreadNum(int numThreads) {
    numThreads_ = numThreads;
}

// 启动线程池
void EventLoopThreadPool::start(const ThreadInitCallback& cb) {
    // 标记线程池已启动
    started_ = true;

    // 当整个服务端有多个线程（负责运行一个 baseLoop 和多个 subLoop）
    for (int i = 0; i < numThreads_; ++i) {
        // 拼接线程的名称
        char buf[name_.size() + 32] = {0};
        snprintf(buf, sizeof buf, "%s%d", name_.c_str(), i);
        // 创建事件循环线程
        EventLoopThread* t = new EventLoopThread(cb, buf);
        // 将事件循环线程添加到线程池中
        threads_.push_back(std::unique_ptr<EventLoopThread>(t));
        // 启动事件循环线程，并获取该线程对应的事件循环对象，将其添加到事件循环对象的集合中
        loops_.push_back(t->startLoop());
    }

    // 当整个服务端只有一个线程（负责运行 baseLoop），就执行初始化回调操作
    if (numThreads_ == 0 && cb) {
        cb(baseLoop_);
    }
}

// 获取下一个被选中的事件循环（如果工作在多线程中，baseLoop 默认以轮询的方式分配 Channel 给 subLoop）
EventLoop* EventLoopThreadPool::getNextLoop() {
    EventLoop* loop = baseLoop_;

    // 通过轮询方式获取一下个处理事件的 EventLoop
    if (!loops_.empty()) {
        loop = loops_[next_];
        ++next_;
        if (next_ >= loops_.size()) {
            next_ = 0;
        }
    }

    return loop;
}

// 返回所有事件循环
std::vector<EventLoop*> EventLoopThreadPool::getAllLoops() {
    if (loops_.empty()) {
        return std::vector<EventLoop*>(1, baseLoop_);
    } else {
        return loops_;
    }
}

// 返回线程池是否已启动
bool EventLoopThreadPool::started() const {
    return started_;
}

// 返回线程池的名称
const std::string& EventLoopThreadPool::name() const {
    return name_;
}