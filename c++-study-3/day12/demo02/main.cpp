/**
 * 线程间互斥-mutex互斥锁和lock_guard
 * 
 * 模拟车站三个售票窗口同时售票，要求每张票只能卖一次
 */

#include <iostream>
#include <list>
#include <thread>
#include <mutex>

// 互斥锁
std::mutex _mutex;

// 车站一共有 100 张车票
int ticketCount = 100;

void sellTicket(int id) {
    while (ticketCount > 0) {
        // 获取互斥锁（支持在作用域结束时自动解锁）
        std::lock_guard<std::mutex> lock(_mutex);

        // 双重检测
        if (ticketCount > 0) {
            // 执行业务逻辑
            std::cout << "售票窗口 " << id << " 卖出第 " << ticketCount << " 张车票" << std::endl;
            ticketCount--;
        }

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main() {
    const int threadCount = 3;
    std::list<std::thread> threads;

    // 启动三个售票子线程
	for (int i = 0; i < threadCount; i++) {
        threads.push_back(std::thread(sellTicket, i));
    }

    // 阻塞等待三个售票子线程执行结束
    for (std::thread& t : threads) {
        t.join();
	}

    std::cout << "所有售票窗口已经结束售票" << std::endl;

    return 0;
}
