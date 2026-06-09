/**
 * 线程启动、结束，创建线程多法、join，detach
 *
 * (c) 创建线程的其他方式
 */

#include <chrono>
#include <iostream>
#include <thread>

class MyClass {
public:
    // 构造函数
    MyClass() {
        std::cout << "MyClass()" << std::endl;
    }

    // 拷贝构造函数
    MyClass(const MyClass& mc) {
        std::cout << "MyClass(const MyClass &)" << std::endl;
    }

    // 析构函数
    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }

    // 重载 () 操作运算符
    void operator()() {
        std::cout << "sub thread start." << std::endl;
        for (int i = 1; i <= 5; ++i) {
            std::cout << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "sub thread end." << std::endl;
    }
};

int main() {
    std::cout << "main thread start." << std::endl;

    // 定义类对象
    MyClass mc;

    // 创建并启动一个普通线程
    // 注意：这里底层会将 mc 对象复制到子线程里面去，因此即使 mc 对象提前销毁，也不会影响子线程的执行
    std::thread t(mc);

    // 阻塞主线程，让主线程等待子线程执行结束，然后再往下执行
    // 注意：如果这里不让主线程阻塞等待子线程执行结束，会导致程序意外退出（直接崩溃）
    t.join();

    std::cout << "main thread end." << std::endl;
    return 0;
}