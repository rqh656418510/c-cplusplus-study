/**
 * 线程传参详解，detach()大坑，成员函数做线程函数
 *
 * (g) 使用成员函数指针做线程函数
 */

#include <iostream>
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

    // 成员函数
    void thread_run(MyClass &mc) {
        std::cout << "sub thread start." << std::endl;
        // 主线程中使用 std::ref() 强制传递引用后，这里修改的是主线程中的 m_c 对象
        mc.m_i = 300;
        std::cout << "sub thread end." << std::endl;
    }

public:
    int m_i;
};

int main() {
    std::cout << "main thread start." << std::endl;

    // 局部变量
    MyClass m_c(200);

    // 在创建子线程时，使用 std::ref() 强制传递引用作为线程函数参数
    // 第一个参数是成员函数指针，第二个参数是类对象（可以是指针或者引用），第三个参数是真正传递给线程函数的参数
    std::thread t(&MyClass::thread_run, &m_c, std::ref(m_c));

    // 等价于上面的写法
    // std::thread t(&MyClass::thread_run, std::ref(m_c), std::ref(m_c));

    // 注意：如果使用下面这种写法（合法），又会多拷贝一份 m_c 对象，导致线程函数里修改的不是主线程中的 m_c 对象
    // std::thread t(&MyClass::thread_run, m_c, std::ref(m_c));

    // 主线程需等待子线程执行完成才继续往下执行
    t.join();

    std::cout << "main thread end." << std::endl;
    return 0;
}