#include "Thread.h"

#include <semaphore.h>

#include <string>

#include "CurrentThread.h"

std::atomic_int Thread::numCreated_(0);

// 构造函数
Thread::Thread(ThreadFunc func, const std::string& name)
    : started_(false), joined_(false), tid_(0), func_(std::move(func)), name_(name) {
}

// 析构函数
Thread::~Thread() {
    // 如果线程已启动且未被 join
    if (started_ && !joined_) {
        // 设置分离线程（避免资源泄露）
        thread_->detach();
    }
}

// 启动线程
void Thread::start() {
    // 标记线程为已启动
    started_ = true;

    // 声明信号量
    sem_t sem;

    // 初始化信号量
    sem_init(&sem, false, 0);

    // 启动新的线程
    thread_ = std::shared_ptr<std::thread>(new std::thread([&]() {
        // 获取新线程的 ID
        tid_ = CurrentThread::tid();

        // 通知主线程已获取新线程的 ID
        sem_post(&sem);

        // 新线程执行线程函数
        func_();
    }));

    // 阻塞等待新线程获取线程 ID
    sem_wait(&sem);
}

// 等待线程执行结束
void Thread::join() {
    // 如果线程已启动且未被 join
    if (started_ && !joined_) {
        // 标记线程已 join
        joined_ = true;
        // 等待线程执行结束
        thread_->join();
    }
}

// 获取线程 ID
pid_t Thread::tid() {
    return tid_;
}

// 获取线程名称
const std::string& Thread::name() const {
    return name_;
}

// 获取已创建的线程数量
int Thread::numCreated() {
    return numCreated_.load();
}

// 设置线程的默认名称
void Thread::setDefaultName() {
    int num = ++numCreated_;
    if (name_.empty()) {
        char buf[32] = {0};
        snprintf(buf, sizeof buf, "Thread%d", num);
        name_ = buf;
    }
}