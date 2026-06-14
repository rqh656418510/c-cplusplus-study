/**
 * 创建多个线程、数据共享问题分析、案例代码
 *
 * (b) 数据共享问题分析 - 只读的数据
 */

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

// 共享数据
std::vector<int> g_v = {1, 2, 3};

void func(int num) {
    std::cout << "sub thread " << num << " start." << std::endl;
    std::cout << "sub thread " << num << " read " << g_v[0] << ", " << g_v[1] << ", " << g_v[2] << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "sub thread " << num << " end." << std::endl;
}

int main() {
    std::cout << "main thread start." << std::endl;

    std::vector<std::thread> threads;

    // 创建 5 个线程，同时这 5 个线程会立即执行（多个线程之间的启动顺序是不确定的）
    for (int i = 0; i < 5; i++) {
        threads.emplace_back(std::thread(func, i));
    }

    // 等待所有线程执行完毕
    for (std::vector<std::thread>::iterator it = threads.begin(); it != threads.end(); ++it) {
        it->join();
    }

    std::cout << "main thread end." << std::endl;
    return 0;
}