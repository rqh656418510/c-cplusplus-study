#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include<iostream>
#include<functional>
#include<vector>
#include<queue>
#include<unordered_map>
#include<memory>
#include<future>
#include<atomic>
#include<mutex>
#include<condition_variable>
#include<stdexcept>
#include<climits>


////////////////////////////////////////// 线程池核心参数 ///////////////////////////////////////////


// 初始的线程数量（默认是CPU的核心数）
const int INIT_THREAD_SIZE = std::thread::hardware_concurrency();

// 任务队列的最大任务数量
const int TASK_MAX_THRESHHOLD = INT_MAX;

// 线程池Cached模式的最大线程数量
const int THREAD_SIZE_MAX_THRESHHOLD = 1024;

// 线程允许的最大空闲时间（单位秒）
const int THREAD_MAX_IDLE_TIME = 60;

// 线程池支持的模式
enum class PoolMode {
    MODE_FIXED,    // 固定大小线程池
    MODE_CACHED    // 缓存线程池
};


////////////////////////////////////////// 线程类 /////////////////////////////////////////////


class Thread {

public:
    // 线程处理函数对象的类型
    using ThreadHandler = std::function<void(int)>;

    // 线程构造
    Thread(ThreadHandler handler) : threadHandler_(handler), threadId_(generateId_++) {

    }

    // 线程析构
    ~Thread() {

    }

    // 启动线程
    void start() {
        // 创建一个线程，并执行线程处理函数
        std::thread t(threadHandler_, threadId_);

        // 将子线程设置为分离线程
        t.detach();
    }

    // 获取线程ID
    int getId() const {
        return threadId_;
    }

private:
    int threadId_;                    // 线程ID
    static int generateId_;           // 用于辅助生成全局唯一的线程ID
    ThreadHandler threadHandler_;     // 线程处理函数
};

// 初始化用于辅助生成全局唯一的线程ID
int Thread::generateId_ = 0;


////////////////////////////////////////// 线程池类 /////////////////////////////////////////////


class ThreadPool {

public:
    // 线程池构造
    ThreadPool() {
        idleThreadSize_ = 0;
        curThreadSize_ = INIT_THREAD_SIZE;
        initThreadSize_ = INIT_THREAD_SIZE;
        threadSizeMaxThreshHold_ = THREAD_SIZE_MAX_THRESHHOLD;
        taskSize_ = 0;
        taskQueMaxThreshHold_ = TASK_MAX_THRESHHOLD;
        poolMode_ = PoolMode::MODE_FIXED;
        isPoolRuning_ = false;
    }

    // 线程池析构
    ~ThreadPool() {
        // 设置线程池的运行状态
        isPoolRuning_ = false;

        // 获取互斥锁，用于等待线程池里面所有的线程结束运行（线程有两种状态：阻塞等待获取任务 & 正在执行任务中）
        std::unique_lock<std::mutex> lock(taskQueMtx_);

        // 必须先获取互斥锁，然后再唤醒所有正在等待获取任务的线程，避免发生线程死锁问题
        notEmpty_.notify_all();

        // 等待线程池里的所有线程回收完成
        allExit_.wait(lock, [this]() { return threads_.size() == 0; });
    }

    // 设置线程池的工作模式
    void setMode(PoolMode mode) {
        if (!checkRunningState()) {
            poolMode_ = mode;
        }
    }

    // 设置线程池Cached模式的最大线程数量
    void setThreadSizeMaxThreshHold(int threshhold) {
        if (PoolMode::MODE_CACHED == poolMode_ && !checkRunningState()) {
            threadSizeMaxThreshHold_ = threshhold;
        }
    }

    // 设置任务队列的最大任务数量
    void setTaskQueMaxThreshHold(size_t threshhold) {
        if (!checkRunningState()) {
            taskQueMaxThreshHold_ = threshhold;
        }
    }

    // 启动线程池
    void start(int initThreadSize) {
        // 设置线程池的运行状态
        isPoolRuning_ = true;

        // 记录初始的线程数量
        initThreadSize_ = initThreadSize;

        // 记录当前线程池的线程数量
        curThreadSize_ = initThreadSize;

        // 创建初始的线程
        for (int i = 0; i < initThreadSize_; i++) {
            // 创建线程对象，并将线程处理函数传递给线程对象的构造函数
            std::unique_ptr<Thread> thread = std::make_unique<Thread>(std::bind(&ThreadPool::threadHandler, this, std::placeholders::_1));
            // 将线程对象放入线程集合中
            threads_.emplace(thread->getId(), std::move(thread));
        }

        // 启动初始的线程
        for (int i = 0; i < initThreadSize_; i++) {
            threads_[i]->start();    // 启动一个线程去执行线程处理函数
            idleThreadSize_++;       // 记录初始空闲线程的数量
        }
    }

    // 提交任务给线程池（使用可变参数模板 + 引用折叠 + 完美转发）
    template<typename Func, typename... Args>
    auto submitTask(Func&& func, Args&&...args) -> std::future<decltype(func(args...))> {
        // 推导任务执行结果的类型（返回值类型）
        using RType = decltype(func(args...));

        // 封装一个任意可调用对象（函数、函数对象、Lambda表达式等）为异步任务
        auto task = std::make_shared<std::packaged_task<RType()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...));

        // 获取与异步任务关联的Future，方便用户获取任务执行结果
        std::future<RType> future = task->get_future();

        // 获取互斥锁
        std::unique_lock<std::mutex> lock(taskQueMtx_);

        // 等待任务队列有空余位置（不满）
        bool waitResult = notFull_.wait_for(lock, std::chrono::seconds(1), [this]() { return taskQueue_.size() < taskQueMaxThreshHold_; });
        // 如果等待超时，则直接返回Future
        if (!waitResult) {
            // 打印错误信息
            std::cerr << "task queue is full, submit task failed.";
            // 封装一个空的任务
            auto task = std::make_shared<std::packaged_task<RType()>>([]()->RType { return RType(); });
            // 执行一个空的任务
            (*task)();
            // 返回与任务关联的Future
            return task->get_future();
        }

        // 如果任务队列有空余位置（不满），则将任务放入任务队列中
        taskQueue_.emplace([task](){
            (*task)();
        });

        // 更新当前任务队列的任务数量
        taskSize_++;

        // 因为刚放入了新任务，任务队列肯定不为空，通知线程池中的线程去执行任务
        notEmpty_.notify_all();

        // 线程池Cached模式的处理，根据任务数量动态增加线程池的线程数量
        if (PoolMode::MODE_CACHED == poolMode_ && taskSize_ > idleThreadSize_ && curThreadSize_ < threadSizeMaxThreshHold_) {
            // 打印日志信息
            std::cout << "expand and create new thread." << std::endl;
            // 创建新线程对象，并将线程处理函数传递给线程对象的构造函数
            std::unique_ptr<Thread> thread = std::make_unique<Thread>(std::bind(&ThreadPool::threadHandler, this, std::placeholders::_1));
            // 获取线程ID（必须在线程放入线程集合之前获取一次线程ID，否则后续将可能获取到空值）
            int threadId = thread->getId();
            // 将新线程对象放入线程集合中
            threads_.emplace(threadId, std::move(thread));
            // 启动新线程
            threads_[threadId]->start();
            // 更新空闲线程的数量
            idleThreadSize_++;
            // 更新当前线程池的线程数量
            curThreadSize_++;
        }

        // 返回与任务关联的Future
        return future;
    }

    // 禁止拷贝构造
    ThreadPool(const ThreadPool &) = delete;

    // 禁止赋值
    ThreadPool &operator=(const ThreadPool &) = delete;

private:
    // 线程处理函数（负责执行任务）
    void threadHandler(int threadId) {
        // 记录当前线程首次运行的时间
        auto lastTime = std::chrono::high_resolution_clock().now();

        // For死循环，为了实现在线程池结束时，所有任务必须执行完成，线程池才可以回收线程
        for (;;) {
            // 获取互斥锁
            std::unique_lock<std::mutex> lock(taskQueMtx_);

            // 打印日志信息
            std::cout << "thread " << std::this_thread::get_id() << " 等待获取任务..." << std::endl;

            // 让当前线程等待获取任务，使用While循环避免虚假唤醒
            while (taskQueue_.size() == 0) {
                // 如果任务列表为空，且线程池要结束运行，则回收当前线程
                if (!checkRunningState()) {
                    // 从线程集合中删除当前线程
                    threads_.erase(threadId);
                    // 唤醒等待线程池回收完毕的线程
                    allExit_.notify_all();
                    // 打印日志信息
                    std::cout << "thread pool destroy, thread " << std::this_thread::get_id() << " exited." << std::endl;
                    // 结束线程处理函数的执行，相当于结束当前线程
                    return;
                }
                // 线程池Cached模式的处理,由于Cached模式下有可能已经创建了很多的线程，但是空闲时间超过最大阀值，因此需要将多余的空闲线程回收掉
                if (PoolMode::MODE_CACHED == poolMode_) {
                    std::cv_status waitResult = notEmpty_.wait_for(lock, std::chrono::seconds(1));
                    // 需要区分超时返回，还是线程正常被唤醒返回
                    if (std::cv_status::timeout == waitResult) {
                        auto nowTime = std::chrono::high_resolution_clock().now();
                        auto duration = std::chrono::duration_cast<std::chrono::seconds>(nowTime - lastTime);
                        // 当线程的空闲时间超过最大阀值，且当前线程池的线程数量大于初始线程数量，则开始回收线程池中的空闲线程
                        if (duration.count() > THREAD_MAX_IDLE_TIME && curThreadSize_ > initThreadSize_) {
                            // 从线程集合中删除当前线程
                            threads_.erase(threadId);
                            // 更新空闲线程的数量
                            idleThreadSize_--;
                            // 更新当前线程池的线程数量
                            curThreadSize_--;
                            // 打印日志信息
                            std::cout << "idle thread " << std::this_thread::get_id() << " exited." << std::endl;
                            // 结束线程处理函数的执行，相当于结束当前线程
                            return;
                        }
                    }
                }
                // 线程池Fixed模式的处理
                else {
                    // 等待任务队列不为空
                    notEmpty_.wait(lock);
                }
            }

            // 更新空闲线程数量（在当前线程执行任务之前）
            idleThreadSize_--;

            // 从任务队列中获取需要执行的任务
            Task task = taskQueue_.front();

            // 将任务从任务队列中移除
            taskQueue_.pop();
            taskSize_--;

            // 打印日志信息
            std::cout << "thread " << std::this_thread::get_id() << " 成功获取任务..." << std::endl;

            // 如果获取了任务之后，任务队列依旧不为空，则继续通知其他线程执行任务
            if (taskQueue_.size() > 0) {
                notEmpty_.notify_all();
            }

            // 因为刚获取了任务，任务队列肯定有空余位置（不满），通知用户提交任务到线程池
            notFull_.notify_all();

            // 释放互斥锁（在当前线程执行任务之前）
            lock.unlock();

            // 当前线程负责执行任务
            if (task != nullptr) {
                task();
            }

            // 更新空闲线程数量（在当前线程执行完任务之后）
            idleThreadSize_++;

            // 更新当前线程最后执行完任务的时间
            lastTime = std::chrono::high_resolution_clock().now();
        }
    }

    // 检查线程池的运行状态
    bool checkRunningState() const {
        return isPoolRuning_;
    }

private:
    std::unordered_map<int, std::unique_ptr<Thread>> threads_;        // 线程集合
    PoolMode poolMode_;                                               // 线程池的模式
    std::atomic_bool isPoolRuning_;                                   // 表示线程池是否正在运行

    size_t initThreadSize_;                                           // 初始的线程数量
    std::atomic_int idleThreadSize_;                                  // 空闲线程的数量
    std::atomic_int curThreadSize_;                                   // 当前线程池的线程数量
    int threadSizeMaxThreshHold_;                                     // 线程池Cached模式的最大线程数量

    using Task = std::function<void()>;                               // 类型重定义，使用Function类模板作为任务
    std::queue<Task> taskQueue_;                                      // 任务队列
    std::atomic_uint taskSize_;                                       // 当前任务队列的任务数量
    size_t taskQueMaxThreshHold_;                                     // 任务队列的最大任务数量

    std::mutex taskQueMtx_;                                           // 任务队列操作的互斥锁
    std::condition_variable notFull_;                                 // 表示任务队列不满，用于通知用户线程提交任务
    std::condition_variable notEmpty_;                                // 表示任务队列不空，用于通知线程池执行任务
    std::condition_variable allExit_;                                 // 表示等待线程池回收所有线程
};

#endif // THREAD_POOL_H
