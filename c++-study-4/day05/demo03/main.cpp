/**
 * 创建多个线程、数据共享问题分析、案例代码
 *
 * (a) 创建和等待多个线程
 */

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

void func(int num) {
    std::cout << "sub thread " << num << " start." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "sub thread " << num << " end." << std::endl;
}

int main() {
    std::cout << "main thread start." << std::endl;

    std::vector<std::thread> threads;

    // 创建 10 个线程，同时这 10 个线程会立即执行（多个线程之间的启动顺序是不确定的）
    for (int i = 0; i < 10; i++) {
        threads.emplace_back(std::thread(func, i));
    }

    // 等待所有线程执行完毕
    for (std::vector<std::thread>::iterator it = threads.begin(); it != threads.end(); ++it) {
        it->join();
    }

    std::cout << "main thread end." << std::endl;
    return 0;
}