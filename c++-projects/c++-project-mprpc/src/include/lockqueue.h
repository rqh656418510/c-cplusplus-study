#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

// 异步写日志的日志队列（线程安全）
template <typename T>
class LockQueue {
public:
    // 往队尾插入数据
    void Push(const T& data) {
        // 获取互斥锁
        std::lock_guard<std::mutex> lock(m_mutex);

        // 插入数据
        m_queue.push(data);

        // 唤醒日志写入线程去消费队列中的数据
        m_condvariable.notify_one();
    }

    // 往队头弹出数据
    T Pop() {
        // 获取互斥锁
        std::lock_guard<std::mutex> lock(m_mutex);

        // 阻塞等待，直到队列不为空
        m_condvariable.wait([this]() { return !m_queue.empty(); });

        // 获取队头元素
        T data = m_queue.front();

        // 弹出队头元素
        m_queue.pop();

        return data;
    }

private:
    std::mutex m_mutex;                      // 互斥锁
    std::queue<T> m_queue;                   // 队列
    std::condition_variable m_condvariable;  // 条件变量
};