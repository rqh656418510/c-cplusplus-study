/**
 * 单例设计模式共享数据分析、解决，call_once
 *
 * (f) 通过 std::once() 保证单例模式的线程安全
 */

#include <iostream>
#include <mutex>
#include <thread>

class MyClass {
private:
    // 私有构造函数
    MyClass() {
        std::cout << "MyClass()" << std::endl;
    }

    // 私有析构函数
    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }

    // 删除拷贝构造函数
    MyClass(const MyClass&) = delete;

    // 删除赋值操作运算符
    MyClass& operator=(const MyClass&) = delete;

    // 创建单例对象（私有静态方法）
    static void createInstance() {
        m_instance = new MyClass();
    }

public:
    // 获取单例对象（静态方法），返回引用，避免指针被调用者误删
    static MyClass& getInstance() {
        // 创建单例对象（永远只执行一次）
        std::call_once(m_flag, createInstance);
        return *m_instance;
    }

private:
    static std::once_flag m_flag;  // 一次性标记
    static MyClass* m_instance;    // 单例对象（静态变量）
};

// 类外初始化静态变量（一次性标记）
std::once_flag MyClass::m_flag;

// 类外初始化静态变量（单例对象）
MyClass* MyClass::m_instance(nullptr);

// 线程函数
void run() {
    MyClass& ptr = MyClass::getInstance();
    std::cout << "address: " << &ptr << std::endl;
}

int main() {
    std::thread t1(run);
    std::thread t2(run);
    std::thread t3(run);

    // 等待子线程执行完成
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
