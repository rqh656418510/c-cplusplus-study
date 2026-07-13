/**
 * condition_variable、wait() 使用
 */

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

using namespace std;

class MyClass {
public:
    // 将收到的玩家命令写入队列
    void inMsgRecvQueue() {
        for (int i = 0; i < 1000; ++i) {
            // 加锁
            std::unique_lock<std::mutex> lock(msgRecvQueueMutex);

            // 插入队列
            msgRecvQueue.push_back(i);

            // 解锁
            lock.unlock();

            // 唤醒一个正在等待的线程
            condtion.notify_one();

            // 模拟网络收包间隔
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        // 加锁
        std::unique_lock<std::mutex> lock(msgRecvQueueMutex);

        // 更新程序停止标记
        stop = true;

        // 解锁
        lock.unlock();

        // 唤醒所有等待线程，让其检测 stop 标记并退出
        condtion.notify_all();
    }

    // 从队列中读取玩家命令
    void outMsgRecvQueue() {
        while (true) {
            // 每轮循环重新初始化
            int command = -1;

            // 加锁
            std::unique_lock<std::mutex> lock(msgRecvQueueMutex);

            // 等待条件满足
            // 如果 Lambda 表达式返回 true，当前线程会继续往下执行（持有锁）
            // 如果 Lambda 表达式返回 false，那么 wait() 将解锁互斥量（释放锁），并让当前线程阻塞等待直到被唤醒
            // wait(lock, predicate) 内部会循环判断 predicate（断言），可以有效避免虚假唤醒
            condtion.wait(lock, [this]() { return stop || !msgRecvQueue.empty(); });

            // 如果程序停止，并且消息队列已经处理完，则退出线程
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

            // 解锁
            lock.unlock();

            // 打印
            if (command != -1) {
                std::cout << "已处理玩家命令: " << command << std::endl;
            }

            // 模拟业务执行耗时
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

private:
    bool stop = false;                 // 程序停止标记
    std::list<int> msgRecvQueue;       // 消息队列（共享数据）
    std::mutex msgRecvQueueMutex;      // 保护消息队列线程安全的互斥锁
    std::condition_variable condtion;  // 条件变量
};

int main() {
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

    return 0;
}