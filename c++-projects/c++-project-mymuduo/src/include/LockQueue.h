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
        std::lock_guard<std::mutex> lock(m_mutex);

        // 插入数据
        m_queue.push(data);

        // 唤醒日志写入线程去消费队列中的数据
        m_condvariable.notify_all();
    }

    // 往队头弹出数据
    T Pop() {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(m_mutex);

        // 阻塞等待，直到队列不为空或者已退出
        m_condvariable.wait(lock, [this]() { return !m_queue.empty() || m_exit; });

        // 视业务逻辑而定，可以返回空数据或者抛出异常
        if (m_exit && m_queue.empty()) {
            return {};
        }

        // 获取队头元素
        T data = m_queue.front();

        // 弹出队头元素
        m_queue.pop();

        return data;
    }

    // 关闭队列
    void Stop() {
        // 获取互斥锁
        std::lock_guard<std::mutex> lock(m_mutex);
        // 设置退出标志
        m_exit = true;
        // 唤醒正在等待的日志写入线程
        m_condvariable.notify_all();
    }

    // 获取退出标志
    bool isExit() const {
        return m_exit;
    }

private:
    std::mutex m_mutex;                      // 互斥锁
    std::queue<T> m_queue;                   // 队列
    std::condition_variable m_condvariable;  // 条件变量
    bool m_exit = false;                     // 退出标志，用于避免发生线程死锁
};
