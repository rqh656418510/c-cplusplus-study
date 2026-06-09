/**
 * 线程传参详解，detach()大坑，成员函数做线程函数
 *
 * (b) 传递临时对象作为线程参数 - 要避免的陷阱代码一
 */

#include <iostream>
#include <thread>

// 定义普通函数（带参数）
// (1) 这里的 i 并不真的是 m_i 的引用，实际上是值传递，即使子线程执行了 detach() 后，在子线程中继续使用 i 也是安全的
// (2) 这里的 buf 是真正指向 m_buf 的指针，当子线程执行了 detach() 后，在子线程中继续使用 buf 是不安全的（存在未定义行为）
void func(const int &i, char *buf) {
    std::cout << "sub thread start." << std::endl;
    std::cout << i << std::endl;
    std::cout << buf << std::endl;
    std::cout << "sub thread end." << std::endl;
}

int main() {
    std::cout << "main thread start." << std::endl;

    // 局部变量
    int m_i = 100;
    char m_buf[] = "this is a string";

    // 创建线程，并传递参数
    std::thread t(func, m_i, m_buf);

    // 将主线程与子线程分离（即子线程变为守护线程），主线程无需等待子线程执行完成才继续往下执行
    t.detach();

    std::cout << "main thread end." << std::endl;
    return 0;
}