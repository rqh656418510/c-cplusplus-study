/**
 * 创建多个线程、数据共享问题分析、案例代码
 *
 * (d) 共享数据的保护
 */

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

class MyClass {
public:
    // 将收到的玩家命令写入队列（生产者）
    void inMsgRecvQueue() {
        for (int i = 0; i < 1000; i++) {
            {
                // 获取互斥锁（作用域结束后会自动释放锁）
                std::lock_guard<std::mutex> lock(msgRecvQueueMutex);

                // 将玩家命令写入队列
                msgRecvQueue.push_back(i);
            }

            // 唤醒等待操作队列的其他线程
            queueNotEmptyCondition.notify_one();

            // 模拟网络收包间隔
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        // 通知消费者退出
        {
            std::lock_guard<std::mutex> lock(msgRecvQueueMutex);
            stop = true;
        }

        // 唤醒所有等待线程
        queueNotEmptyCondition.notify_all();
    }

    // 从队列中读取玩家命令（消费者）
    void outMsgRecvQueue() {
        while (true) {
            // 获取互斥锁（作用域结束后会自动释放锁）
            std::unique_lock<std::mutex> lock(msgRecvQueueMutex);

            // 当前线程等待队列不为空或者收到退出信号
            queueNotEmptyCondition.wait(lock, [this]() { return stop || !msgRecvQueue.empty(); });

            // 收到退出信号且队列为空
            if (stop && msgRecvQueue.empty()) {
                break;
            }

            // 取出队列元素
            int command = msgRecvQueue.front();

            // 移除队列元素
            msgRecvQueue.pop_front();

            // 尽早释放锁，提高并发性能
            lock.unlock();

            // 解析并执行玩家命令
            handleCommand(command);
        }
    }

private:
    // 模拟处理玩家命令
    void handleCommand(int command) {
        std::cout << "已处理玩家命令: " << command << std::endl;
    }

private:
    std::list<int> msgRecvQueue;                     // 消息队列（共享数据）
    std::mutex msgRecvQueueMutex;                    // 保护消息队列线程安全的互斥锁
    std::condition_variable queueNotEmptyCondition;  // 消息队列不为空的条件
    bool stop = false;                               // 线程退出标志
};

int main() {
    // 局部变量
    MyClass mc;

    // 创建并启动写线程（生产者）
    std::thread t_write(&MyClass::inMsgRecvQueue, &mc);

    // 创建并启动读线程（消费者）
    std::thread t_read(&MyClass::outMsgRecvQueue, &mc);

    // 等待写线程执行完毕
    t_write.join();

    // 等待读线程执行完毕
    t_read.join();

    return 0;
}