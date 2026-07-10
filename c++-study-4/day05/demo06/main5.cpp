/**
 * 单例设计模式共享数据分析、解决，call_once
 *
 * (e) 单例设计模式共享数据问题分析
 */

#include <iostream>
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

public:
    // 获取单例对象（静态方法）
    static MyClass* getInstance() {
        if (m_instance == nullptr) {
            // 初始化单例对象
            m_instance = new MyClass();
        }

        // 返回单例对象
        return m_instance;
    }

private:
    static MyClass* m_instance;  // 单例对象（静态变量）
};

// 类外初始化静态变量（单例对象）
MyClass* MyClass::m_instance(nullptr);

// 线程函数
void run() {
    MyClass* ptr = MyClass::getInstance();
    std::cout << "address: " << ptr << std::endl;
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