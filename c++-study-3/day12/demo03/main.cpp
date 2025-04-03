/**
 * 线程间同步通信-生产者消费者模型
 * 
 * <p> 生产者生产一个商品，通知消费者消费一个商品，消费完再通知生产者继续生产商品
 */

#include <iostream>
#include <ctime>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

// 自定义队列（线程安全）
class MyQueue {

public:

    // 入队
    void push(int value) {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(_mutex);

        // 如果队列不为空，则阻塞等待直到满足条件为止（避免虚假唤醒），阻塞等待期间会释放互斥锁
        if (!_queue.empty()) {
			_cv.wait(lock, [this] {return _queue.empty(); });
        }

        // 插入队列元素
        _queue.push(value);

        // 通知消费者消费
        _cv.notify_all();
    }

    // 出队
    int pop() {
        // 获取互斥锁
        std::unique_lock<std::mutex> lock(_mutex);

        // 如果队列为空，则阻塞等待直到满足条件为止（避免虚假唤醒），阻塞等待期间会释放互斥锁
        if (_queue.empty()) {
			_cv.wait(lock, [this] {return !_queue.empty(); });
        }

        // 弹出队列元素
        int value = _queue.front();
		_queue.pop();

        // 通知生产者生产
        _cv.notify_all();

		return value;
    }

private:
    std::mutex _mutex;              // 互斥锁
    std::queue<int> _queue;         // 队列（非线程安全）
    std::condition_variable _cv;    // 条件变量
};

void producerTask(MyQueue * queue) {
    while (true) {
        int newValue = std::rand() % 100 + 1;
        queue->push(newValue);
        std::cout << "生产者生产 " << newValue << " 号商品" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void consumerTask(MyQueue* queue) {
    while (true) {
        int value = queue->pop();
        std::cout << "消费者消费 " << value << " 号商品" << std::endl;
    }
}

int main() {
    // 设置随机种子
    srand(time(nullptr));

    // 共享队列
    MyQueue queue;

    // 生产者线程
    std::thread producerThread(producerTask, &queue);

    // 消费者线程
    std::thread consumerThread(consumerTask, &queue);

    // 主线程等待子线程结束
    producerThread.join();
    consumerThread.join();

    return 0;
}
