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
        : m_exited(false){

          };

    // 析构函数
    ~LockQueue() {
        if (!m_exited) {
            Stop();
        }
    }

    // 往队尾插入数据
    void Push(const T& data) {
        {
            // 获取互斥锁
            std::lock_guard<std::mutex> lock(m_mutex);

            // 如果已经退出，则不再接受新数据（防御性）
            if (m_exited) {
                return;
            }

            // 插入数据
            m_queue.push(data);
        }

        // 唤醒日志写入线程去消费队列中的数据
        m_cv.notify_one();
    }

    // 往队尾插入数据（支持右值，减少一次拷贝）
    void Push(T&& data) {
        {
            // 获取互斥锁
            std::lock_guard<std::mutex> lock(m_mutex);

            // 如果已经退出，则不再接受新数据（防御性）
            if (m_exited) {
                return;
            }

            // 插入数据
            m_queue.push(std::move(data));
        }

        // 唤醒日志写入线程去消费队列中的数据
        m_cv.notify_one();
    }

    // 往队头弹出数据
    T Pop() {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(m_mutex);

        // 阻塞等待，直到队列不为空或者已退出
        m_cv.wait(lock, [this]() { return !m_queue.empty() || m_exited; });

        // 视业务逻辑而定，可以返回空数据或者抛出异常
        if (m_exited || m_queue.empty()) {
            // 返回空数据（要求队列中的元素有空构造函数）
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
        {
            // 获取互斥锁
            std::lock_guard<std::mutex> lock(m_mutex);
            // 设置退出标志
            m_exited = true;
        }

        // 唤醒正在等待的日志写入线程
        m_cv.notify_all();
    }

    // 获取退出标志
    bool isExit() const {
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
    std::mutex m_mutex;            // 互斥锁
    std::queue<T> m_queue;         // 队列
    std::condition_variable m_cv;  // 条件变量
    std::atomic_bool m_exited;     // 退出标志，用于避免发生线程死锁
};