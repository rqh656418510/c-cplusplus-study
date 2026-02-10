#pragma once

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

// 有界阻塞队列（生产者/消费者队列，线程安全）
template <typename T>
class LockQueue {
public:
    // 构造函数
    explicit LockQueue(size_t maxSize = 4096) : m_maxSize(maxSize), m_exited(false) {
    }

    // 析构函数
    ~LockQueue() {
        if (!m_exited) {
            Stop();
        }
    }

    // 往队尾插入数据（左值）
    void Push(const T& data) {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(m_mutex);

        // 阻塞等待，直到队列有空间或已退出
        m_cvNotFull.wait(lock, [this]() { return m_queue.size() < m_maxSize || m_exited; });

        // 如果队列已经退出，则不再接受新数据
        if (m_exited) {
            return;
        }

        // 插入数据
        m_queue.push(data);

        // 唤醒等待取数据的线程
        m_cvNotEmpty.notify_one();
    }

    // 往队尾插入数据（右值，减少拷贝）
    void Push(T&& data) {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(m_mutex);

        // 阻塞等待，直到队列有空间或已退出
        m_cvNotFull.wait(lock, [this]() { return m_queue.size() < m_maxSize || m_exited; });

        // 如果队列已经退出，则不再接受新数据
        if (m_exited) {
            return;
        }

        // 插入数据
        m_queue.push(std::move(data));

        // 唤醒等待取数据的线程
        m_cvNotEmpty.notify_one();
    }

    // 往队头弹出数据
    T Pop() {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(m_mutex);

        // 阻塞等待，直到队列不为空或已退出
        m_cvNotEmpty.wait(lock, [this]() { return !m_queue.empty() || m_exited; });

        // 只有在已退出且队列为空时，才真正返回空数据，否则继续执行直到队列为空为止
        if (m_exited && m_queue.empty()) {
            // 返回空数据（要求队列元素有默认构造函数）
            return {};
        }

        // 获取队头元素
        T data = std::move(m_queue.front());

        // 弹出队头元素
        m_queue.pop();

        // 唤醒等待插入数据的线程
        m_cvNotFull.notify_one();

        return data;
    }

    // 关闭队列
    void Stop() {
        {
            // 获取互斥锁
            std::lock_guard<std::mutex> lock(m_mutex);
            // 更新退出标记
            m_exited = true;
        }

        // 唤醒正在等待的线程
        m_cvNotEmpty.notify_all();
        m_cvNotFull.notify_all();
    }

    // 获取退出标志
    bool IsExited() const {
        return m_exited;
    }

    // 获取队列大小
    size_t Size() const {
        // 获取互斥锁
        std::lock_guard<std::mutex> lock(m_mutex);
        // 返回队列大小
        return m_queue.size();
    }

private:
    size_t m_maxSize;                      // 队列最大容量
    std::mutex m_mutex;                    // 互斥锁
    std::queue<T> m_queue;                 // 队列
    std::condition_variable m_cvNotEmpty;  // 队列非空条件
    std::condition_variable m_cvNotFull;   // 队列非满条件
    std::atomic_bool m_exited;             // 退出标志
};