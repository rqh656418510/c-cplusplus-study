/**
 * 生产者和消费者模型
 *
 * <p> 模拟实现生产者线程生产一条数据，消费者线程就消费一条数据，两个线程一直交替执行
 */

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <condition_variable>

using namespace std;

mutex _mutex;                // 互斥锁
queue<int> _queue;           // 共享数据队列
condition_variable _cv;      // 条件变量
atomic_bool _finish(false);  // 控制标志（用于终止程序）

void produce() {
    while (!_finish) {
        // 获取锁
        unique_lock<mutex> lock(_mutex);

        // 避免虚假唤醒，只有满足条件才会继续执行
        _cv.wait(lock, [] { return _queue.empty(); });

        // 模拟生产时间
        this_thread::sleep_for(chrono::milliseconds(500));

        int item = rand() % 1000 + 1;
        _queue.push(item);
        cout << "生产: " << item << endl;

        // 通知消费者
        _cv.notify_all();
    }
}

void consume() {
    while (!_finish) {
        // 获取锁
        unique_lock<mutex> lock(_mutex);

        // 避免虚假唤醒，只有满足条件才会继续执行
        _cv.wait(lock, [] { return !_queue.empty(); });

        // 模拟消费时间
        this_thread::sleep_for(chrono::milliseconds(500));

        int item = _queue.front();
        _queue.pop();
        cout << "消费: " << item << endl;

        // 通知生产者
        _cv.notify_all();
    }
}

int main() {
    // 设置随机种子
    srand(time(nullptr));

    // 启动生产者和消费者线程
    thread producer(produce);
    thread consumer(consume);

    // 主线程运行 60 秒
    this_thread::sleep_for(chrono::seconds(60));

    // 设置终止标志
    _finish = true;

    // 唤醒所有线程，确保它们能结束
    _cv.notify_all();

    // 等待生产者和消费者线程结束
    producer.join();
    consumer.join();

    return 0;
}