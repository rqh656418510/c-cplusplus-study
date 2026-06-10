/**
 * 线程传参详解，detach()大坑，成员函数做线程函数
 *
 * (c) 传递临时对象作为线程参数 - 要避免的陷阱代码二
 */

#include <iostream>
#include <string>
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

    int get() const {
        return m_i;
    }

private:
    int m_i;
};

// 定义普通函数（带参数）
void func(const int &i, const MyClass &mc) {
    std::cout << "sub thread start." << std::endl;
    std::cout << i << std::endl;
    std::cout << mc.get() << std::endl;
    std::cout << "sub thread end." << std::endl;
}

int main() {
    std::cout << "main thread start." << std::endl;

    // 局部变量
    int m_i = 100;
    int m_c = 200;

    // 创建线程，并传递参数（这里的 m_c 会通过隐式类型转换生成一个临时 MyClass 对象）
    std::thread t(func, m_i, m_c);

    // 将主线程与子线程分离（即子线程变为守护线程），主线程无需等待子线程执行完成才继续往下执行
    t.detach();

    std::cout << "main thread end." << std::endl;
    return 0;
}
