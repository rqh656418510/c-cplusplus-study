#pragma once

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

#include "NonCopyable.h"

// 有界阻塞队列（生产者/消费者队列，线程安全）
template <typename T>
class LockQueue : NonCopyable {
public:
    // 构造函数
    explicit LockQueue(size_t maxSize = 4096) : maxSize_(maxSize), exited_(false) {
    }

    // 析构函数
    ~LockQueue() {
        if (!exited_) {
            stop();
        }
    }

    // 往队尾插入数据（左值）
    void push(const T& data) {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(mutex_);

        // 阻塞等待，直到队列有空间或已退出
        cvNotFull_.wait(lock, [this]() { return queue_.size() < maxSize_ || exited_; });

        // 如果队列已经退出，则不再接受新数据
        if (exited_) {
            return;
        }

        // 插入数据
        queue_.push(data);

        // 唤醒等待取数据的线程
        cvNotEmpty_.notify_one();
    }

    // 往队尾插入数据（右值，减少拷贝）
    void push(T&& data) {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(mutex_);

        // 阻塞等待，直到队列有空间或已退出
        cvNotFull_.wait(lock, [this]() { return queue_.size() < maxSize_ || exited_; });

        // 如果队列已经退出，则不再接受新数据
        if (exited_) {
            return;
        }

        // 插入数据
        queue_.push(std::move(data));

        // 唤醒等待取数据的线程
        cvNotEmpty_.notify_one();
    }

    // 往队头弹出数据
    T pop() {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(mutex_);

        // 阻塞等待，直到队列不为空或已退出
        cvNotEmpty_.wait(lock, [this]() { return !queue_.empty() || exited_; });

        // 只有在已退出且队列为空时，才真正返回空数据，否则继续执行直到队列为空为止
        if (exited_ && queue_.empty()) {
            // 返回空数据（要求队列元素有默认构造函数）
            return {};
        }

        // 获取队头元素
        T data = std::move(queue_.front());

        // 弹出队头元素
        queue_.pop();

        // 唤醒等待插入数据的线程
        cvNotFull_.notify_one();

        return data;
    }

    // 关闭队列
    void stop() {
        {
            // 获取互斥锁
            std::lock_guard<std::mutex> lock(mutex_);
            // 更新退出标记
            exited_ = true;
        }

        // 唤醒正在等待的线程
        cvNotEmpty_.notify_all();
        cvNotFull_.notify_all();
    }

    // 获取退出标志
    bool isExited() const {
        return exited_;
    }

    // 获取队列大小
    size_t size() const {
        // 获取互斥锁
        std::lock_guard<std::mutex> lock(mutex_);
        // 返回队列大小
        return queue_.size();
    }

private:
    size_t maxSize_;                      // 队列最大容量
    std::mutex mutex_;                    // 互斥锁
    std::queue<T> queue_;                 // 队列
    std::condition_variable cvNotEmpty_;  // 队列非空条件
    std::condition_variable cvNotFull_;   // 队列非满条件
    std::atomic_bool exited_;             // 退出标志
};