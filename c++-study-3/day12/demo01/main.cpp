/**
 * 通过thread类编写C++多线程程序
 */

#include <iostream>
#include <thread>

void threadHandler1() {
    // 线程睡眠5秒
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "run thread handler 1" << std::endl;
}

void threadHandler2(int seconds) {
    // 线程睡眠
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    std::cout << "run thread handler 2" << std::endl;
}

int main() {

    // 定义一个线程对象，参数传入一个线程函数，线程会自动启动
    std::thread t1(threadHandler1);

    // 或者指定线程函数的参数
    // std::thread t1(threadHandler2, 5);

    // 主线程等待子线程结束，然后再继续往下执行
    t1.join();

    // 或者将子线程设置为分离线程，这样主线程就不需要等待子线程结束；当主线程结束，所有子线程都自动结束（终止运行）
    // t1.detach();

    return 0;
}
