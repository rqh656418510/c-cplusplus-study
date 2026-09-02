/**
* std::atomic续谈、std::async深入谈
 *
 * （a) std::atomic 深入使用
 */

#include <iostream>

#include <atomic>
#include <thread>

// 定义全局变量（使用原子类型）
static std::atomic<int> g_count(0);

void process() {
    for (int i = 0; i < 1000000; ++i) {
        // 下面这种写法不支持原子操作，存在线程安全问题
        g_count = g_count + 1;
    }
}

int main() {
    // 创建子线程 1
    std::thread t1(process);

    // 创建子线程 2
    std::thread t2(process);

    // 等待子线程 1 执行完成
    t1.join();

    // 等待子线程 2 执行完成
    t2.join();

    // 预期输出结果是：2000000
    std::cout << "count = " << g_count.load() << std::endl;

    return 0;
}
