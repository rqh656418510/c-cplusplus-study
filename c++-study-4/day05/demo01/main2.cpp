/**
 * 线程启动、结束，创建线程多法、join，detach
 *
 * (b) thread 与 detach() 的使用
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

    // 将主线程与子线程分离（即子线程变为守护线程），主线程无需等待子线程执行完成才继续往下执行
    t.detach();

    std::cout << "main thread end." << std::endl;
    return 0;
}