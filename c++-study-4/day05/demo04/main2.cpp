/**
 * 互斥量概念、用法、死锁演示及解决详解
 *
 * (b) mutex + lock_guard 的使用
 */

#include <atomic>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

class MyClass {
public:
    // 将收到的玩家命令写入队列
    void inMsgRecvQueue() {
        for (int i = 0; i < 1000; ++i) {
            {
                // 加锁（出了作用域后会自动解锁）
                std::lock_guard<std::mutex> lock(msgRecvQueueMutex);

                // 插入队列
                msgRecvQueue.push_back(i);
            }

            // 模拟网络收包间隔
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        // 更新程序停止标记
        stop = true;
    }

    // 从队列中读取玩家命令
    void outMsgRecvQueue() {
        while (true) {
            int command = -1;

            {
                // 加锁（出了作用域后会自动解锁）
                std::lock_guard<std::mutex> lock(msgRecvQueueMutex);

                // 判断程序停止标记
                if (stop && msgRecvQueue.empty()) {
                    break;
                }

                // 操作队列
                if (!msgRecvQueue.empty()) {
                    // 取出队列元素
                    command = msgRecvQueue.front();
                    // 移除队列元素
                    msgRecvQueue.pop_front();
                }
            }

            // 打印
            if (command != -1) {
                std::cout << "已处理玩家命令: " << command << std::endl;
            }

            // 模拟业务执行耗时
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

private:
    std::list<int> msgRecvQueue;   // 消息队列（共享数据）
    std::mutex msgRecvQueueMutex;  // 保护消息队列线程安全的互斥锁
    std::atomic_bool stop{false};  // 程序停止标记
};

int main() {
    std::cout << "main thread start." << std::endl;

    // 局部变量
    MyClass mc;

    // 创建并启动写线程
    std::thread t_write(&MyClass::inMsgRecvQueue, &mc);

    // 创建并启动读线程
    std::thread t_read(&MyClass::outMsgRecvQueue, &mc);

    // 等待写线程执行完毕
    t_write.join();

    // 等待读线程执行完毕
    t_read.join();

    std::cout << "main thread end." << std::endl;
    return 0;
}
