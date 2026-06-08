/**
 * 线程启动、结束，创建线程多法、join，detach
 *
 * (a) thread 与 join() 的使用
 */

#include <chrono>
#include <iostream>
#include <thread>

void func() {
    std::cout << "sub thread start." << std::endl;
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "sub thread end." << std::endl;
}

int main() {
    std::cout << "main thread start." << std::endl;

    // 创建并启动一个普通线程
    std::thread t(func);

    // 阻塞主线程，让主线程等待子线程执行结束，然后再往下执行
    // 注意：如果这里不让主线程阻塞等待子线程执行结束，会导致程序意外退出（直接崩溃）
    t.join();

    std::cout << "main thread end." << std::endl;
    return 0;
}