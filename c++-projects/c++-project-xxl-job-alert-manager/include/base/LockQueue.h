#pragma once

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

// 无界阻塞队列（生产者/消费者队列），线程安全
template <typename T>
class LockQueue {
public:
    // 构造函数
    LockQueue()
        : exited_(false){

          };

    // 析构函数
    ~LockQueue() {
        if (!exited_) {
            Stop();
        }
    }

    // 往队尾插入数据
    void Push(const T& data) {
        {
            // 获取互斥锁
            std::lock_guard<std::mutex> lock(mutex_);

            // 如果已经退出，则不再接受新数据（防御性）
            if (exited_) {
                return;
            }

            // 插入数据
            queue_.push(data);
        }

        // 唤醒日志写入线程去消费队列中的数据
        cv_.notify_one();
    }

    // 往队尾插入数据（支持右值，减少一次拷贝）
    void Push(T&& data) {
        {
            // 获取互斥锁
            std::lock_guard<std::mutex> lock(mutex_);

            // 如果队列已经退出，则不再接受新数据
            if (exited_) {
                return;
            }

            // 插入数据
            queue_.push(std::move(data));
        }

        // 唤醒日志写入线程去消费队列中的数据
        cv_.notify_one();
    }

    // 往队头弹出数据
    T Pop() {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(mutex_);

        // 阻塞等待，直到队列不为空或者已退出
        cv_.wait(lock, [this]() { return !queue_.empty() || exited_; });

        // 视业务逻辑而定，可以返回空数据或者抛出异常
        if (exited_ && queue_.empty()) {
            return {};
        }

        // 获取队头元素
        T data = queue_.front();

        // 弹出队头元素
        queue_.pop();

        return data;
    }

    // 关闭队列
    void Stop() {
        {
            // 获取互斥锁
            std::lock_guard<std::mutex> lock(mutex_);
            // 设置退出标志
            exited_ = true;
        }

        // 唤醒正在等待的日志写入线程
        cv_.notify_all();
    }

    // 获取退出标志
    bool isExit() const {
        return exited_;
    }

    // 获取队列大小
    size_t Size() const {
        // 获取互斥锁
        std::lock_guard<std::mutex> lock(mutex_);
        // 返回队列大小
        return queue_.size();
    }

private:
    std::mutex mutex_;            // 互斥锁
    std::queue<T> queue_;         // 队列
    std::condition_variable cv_;  // 条件变量
    std::atomic_bool exited_;     // 退出标志，用于避免发生线程死锁
};