/**
 * windows临界区、其他各种mutex互斥量
 *
 * （a) windows 临界区使用
 */

#include <atomic>
#include <chrono>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <Windows.h>

#define WINDOWS_CRITICAL_SECTION  // 标记 Windows 系统环境

class MyClass {
public:
    // 将收到的玩家命令写入队列
    void inMsgRecvQueue() {
        for (int i = 0; i < 1000; ++i) {
            #ifdef WINDOWS_CRITICAL_SECTION
                // 加锁
                EnterCriticalSection(&winsec);

                // 插入队列
                msgRecvQueue.push_back(i);

                // 解锁
                LeaveCriticalSection(&winsec);
            #else
                {
                    // 加锁（出了作用域后会自动解锁）
                    std::unique_lock<std::mutex> lock(msgRecvQueueMutex);

                    // 插入队列
                    msgRecvQueue.push_back(i);
                }
            #endif

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

            #ifdef WINDOWS_CRITICAL_SECTION
                // 加锁
                EnterCriticalSection(&winsec);

                // 判断程序停止标记
                if (stop && msgRecvQueue.empty()) {
                    // 解锁
                    LeaveCriticalSection(&winsec);
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
                LeaveCriticalSection(&winsec);
            #else 
                {
                    // 加锁（出了作用域后会自动解锁）
                    std::unique_lock<std::mutex> lock(msgRecvQueueMutex);

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
            #endif

            // 打印
            if (command != -1) {
                std::cout << "已处理玩家命令: " << command << std::endl;
            }

            // 模拟业务执行耗时
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    // 构造函数
    MyClass() {
        #ifdef WINDOWS_CRITICAL_SECTION
            InitializeCriticalSection(&winsec);  // 初始化临界区
        #endif
    }

    // 析构函数
    ~MyClass() {
        #ifdef WINDOWS_CRITICAL_SECTION
            DeleteCriticalSection(&winsec);  // 删除临界区
        #endif
    }

private:
    std::list<int> msgRecvQueue;   // 消息队列（共享数据）
    std::mutex msgRecvQueueMutex;  // 保护消息队列线程安全的互斥锁
    std::atomic_bool stop{false};  // 程序停止标记

    #ifdef WINDOWS_CRITICAL_SECTION
        CRITICAL_SECTION winsec;  // Windows 系统中的临界区，作用非常类似于 C++ 11 中的 std::mutex
    #endif
    
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