/**
 * 线程传参详解，detach()大坑，成员函数做线程函数
 *
 * (f) 传递类对象、智能指针作为线程参数 - 传递智能指针
 */

#include <iostream>
#include <memory>
#include <thread>

class MyClass {
public:
    // 有参构造函数
    MyClass(int i) : m_i(i) {
        std::cout << "MyClass()" << std::endl;
    }

    // 拷贝构造函数
    MyClass(const MyClass &mc) : m_i(mc.m_i) {
        std::cout << "MyClass(const MyClass &)" << std::endl;
    }

    // 析构函数
    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }

public:
    int m_i;
};

// 定义普通函数（带参数）
void func(std::unique_ptr<MyClass> up) {
    std::cout << "sub thread start." << std::endl;
    // 主线程中传递智能指针后，这里修改的是主线程中的 m_c 对象
    up->m_i = 300;
    std::cout << "sub thread end." << std::endl;
}

int main() {
    std::cout << "main thread start." << std::endl;

    // 局部变量
    std::unique_ptr<MyClass> m_c(new MyClass(200));

    // 在创建子线程时，传递智能指针作为线程函数参数
    std::thread t(func, std::move(m_c));

    // 主线程需等待子线程执行完成才继续往下执行
    t.join();

    std::cout << "main thread end." << std::endl;
    return 0;
}