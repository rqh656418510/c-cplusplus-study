/**
 * 单例设计模式共享数据分析、解决，call_once
 *
 * (d) 单例设计模式使用 - 懒汉单例模式（基于 DCL 双重检查锁，优化单例对象释放）
 */

#include <atomic>
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

public:
    // 获取单例对象（静态方法）
    static MyClass* getInstance() {
        // 第一次获取单例对象
        MyClass* ptr = m_instance.load(std::memory_order_acquire);

        // 第一次检测单例对象是否为空
        if (ptr == nullptr) {
            // 获取互斥锁
            std::lock_guard<std::mutex> lock(m_mutex);

            // 第二次获取单例对象
            ptr = m_instance.load(std::memory_order_relaxed);

            // 第二次检测单例对象是否为空
            if (ptr == nullptr) {
                // 初始化单例对象
                ptr = new MyClass();

                // 静态局部变量（用于自动释放单例对象的内存）
                static GcClass gc;

                // 设置单例对象
                m_instance.store(ptr, std::memory_order_release);
            }
        }

        // 返回单例对象
        return ptr;
    }

    // 内部定义的 GC 类，用于自动释放单例对象的内存
    class GcClass {
    public:
        // 构造函数
        GcClass() {
        }

        // 析构函数
        ~GcClass() {
            MyClass* ptr = MyClass::getInstance();
            if (ptr == nullptr) {
                // 释放单例对象的内存
                delete ptr;
                ptr = nullptr;
            }
        }
    };

private:
    static std::mutex m_mutex;                // 互斥锁（静态变量）
    static std::atomic<MyClass*> m_instance;  // 单例对象（静态变量）
};

// 类外初始化静态变量（互斥锁）
std::mutex MyClass::m_mutex;

// 类外初始化静态变量（单例对象）
std::atomic<MyClass*> MyClass::m_instance(nullptr);

int main() {
    // 获取单例对象
    MyClass* mc = MyClass::getInstance();
    MyClass* mc2 = MyClass::getInstance();

    // 判断地址是否相同
    std::cout << "address: " << mc << std::endl;
    std::cout << "address: " << mc2 << std::endl;
    std::cout << "equals: " << (mc == mc2 ? "true" : "false") << std::endl;

    return 0;
}