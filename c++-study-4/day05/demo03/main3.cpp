/**
 * 创建多个线程、数据共享问题分析、案例代码
 *
 * (c) 数据共享问题分析 - 有读有写
 */

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

// 共享数据（有读有写）
std::vector<int> g_v = {1, 2, 3};

void func(int num) {
    std::cout << "sub thread " << num << " start." << std::endl;

    // 前两个线程：执行写操作
    if (num < 2) {
        // 写操作：添加一个新元素
        g_v.push_back(num);
        std::cout << "sub thread " << num << " write value " << num << std::endl;
    }
    // 后三个线程：执行读操作
    else {
        // 读操作：读取 vector 的所有元素
        std::cout << "sub thread " << num << " reads: ";
        for (int val : g_v) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    // 模拟一些工作耗时
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::cout << "sub thread " << num << " end." << std::endl;
}

int main() {
    std::cout << "main thread start." << std::endl;

    std::vector<std::thread> threads;

    // 创建 5 个线程，其中 2 个线程执行写操作，3 个线程执行读操作
    // 由于读写同时发生，可能会导致未定义行为（比如读取到不一致的值、程序崩溃等）
    for (int i = 0; i < 5; i++) {
        threads.emplace_back(func, i);
    }

    // 等待所有线程执行完毕
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "main thread end." << std::endl;
    return 0;
}