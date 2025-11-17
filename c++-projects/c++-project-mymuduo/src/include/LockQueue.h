#pragma once

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

#include "noncopyable.h"

// 用于异步写日志的队列（线程安全）
template <typename T>
class LockQueue : noncopyable {
public:
    // 往队尾插入数据
    void Push(const T& data) {
        // 获取互斥锁
        std::lock_guard<std::mutex> lock(mutex_);

        // 插入数据
        queue_.push(data);

        // 唤醒日志写入线程去消费队列中的数据
        condvariable_.notify_all();
    }

    // 往队头弹出数据
    T Pop() {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(mutex_);

        // 阻塞等待，直到队列不为空或者已退出
        condvariable_.wait(lock, [this]() { return !queue_.empty() || exit_; });

        // 视业务逻辑而定，可以返回空数据或者抛出异常
        if (exit_ && queue_.empty()) {
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
        // 获取互斥锁
        std::lock_guard<std::mutex> lock(mutex_);
        // 设置退出标志
        exit_ = true;
        // 唤醒正在等待的日志写入线程
        condvariable_.notify_all();
    }

    // 获取退出标志
    bool isExit() const {
        return exit_;
    }

private:
    std::mutex mutex_;                      // 互斥锁
    std::queue<T> queue_;                   // 队列
    std::condition_variable condvariable_;  // 条件变量
    bool exit_ = false;                     // 退出标志，用于避免发生线程死锁
};
