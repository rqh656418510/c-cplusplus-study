/**
 * 线程启动、结束，创建线程多法、join，detach
 */

#include <chrono>
#include <iostream>
#include <thread>

void func() {
    for (int i = 1; i <= 1000; ++i) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void test01() {
    // 启动一个普通线程
    std::thread t(func);
    // 等待线程执行结束
    t.join();
}

int main() {
    test01();
    return 0;
}