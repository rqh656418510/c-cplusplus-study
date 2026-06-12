/**
 * 线程传参详解，detach()大坑，成员函数做线程函数
 *
 * (d) 传递临时对象作为线程参数 - 线程 ID 的概念
 */

#include <iostream>
#include <string>
#include <thread>

class MyClass {
public:
    // 有参构造函数
    MyClass(int i) : m_i(i) {
        std::cout << "MyClass(), thread id : " << std::this_thread::get_id() << std::endl;
    }

    // 拷贝构造函数
    MyClass(const MyClass &mc) : m_i(mc.m_i) {
        std::cout << "MyClass(const MyClass &), thread id : " << std::this_thread::get_id() << std::endl;
    }

    // 析构函数
    ~MyClass() {
        std::cout << "~MyClass(), thread id : " << std::this_thread::get_id() << std::endl;
    }

    int get() const {
        return m_i;
    }

private:
    int m_i;
};

// 定义普通函数（带参数）
void func(const int &i, const MyClass &mc) {
    std::cout << "sub thread start." << std::endl;
    std::cout << "sub thread id : " << std::this_thread::get_id() << std::endl;
    std::cout << i << std::endl;
    std::cout << mc.get() << std::endl;
    std::cout << "sub thread end." << std::endl;
}

int main() {
    std::cout << "main thread start." << std::endl;
    std::cout << "main thread id : " << std::this_thread::get_id() << std::endl;

    // 局部变量
    int m_i = 100;
    int m_c = 200;

    // 创建线程，并传递参数（构造一个临时对象）
    // 注意：这里的 MyClass 临时对象是在主线程中构造出来的，而且是在主线程结束运行之前构造出来，因此是安全的
    std::thread t(func, m_i, MyClass(m_c));

    // 设置主线程需等待子线程执行完成才继续往下执行
    t.join();

    std::cout << "main thread end." << std::endl;
    return 0;
}
