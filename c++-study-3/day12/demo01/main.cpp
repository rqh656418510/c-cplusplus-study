/**
 * 通过thread类编写C++多线程程序
 */

#include <iostream>
#include <thread>

void threadHandler1() {
    std::cout << "run thread handler 1" << std::endl;
}

int main() {

    // 定义一个线程对象，参数传入一个线程函数
    std::thread t1(threadHandler1);

    // 主线程等待子线程结束，然后再继续往下执行
    t1.join();

    return 0;
}
