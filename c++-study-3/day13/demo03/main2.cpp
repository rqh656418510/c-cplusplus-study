/**
 * 单例模式代码设计
 */

#include <iostream>
#include <mutex>
#include <atomic>

// 懒汉单例模式

using namespace std;

class Singleton {

private:
    // 私有的默认构造函数
    Singleton() noexcept {

    }

    // 删除拷贝构造函数
    Singleton(const Singleton &) = delete;

    // 删除赋值运算符
    Singleton &operator=(const Singleton &) = delete;

public:
    // 获取单例对象（双端检锁 - DCL）
    static Singleton *getInstance() {
        // 获取单例对象
        Singleton *instance = _singleton.load(memory_order_acquire);

        // 第一次检测
        if (instance == nullptr) {
            // 获取互斥锁
            lock_guard<mutex> lock(_mutex);

            // 获取单例对象
            instance = _singleton.load(memory_order_relaxed);

            // 第二次检测
            if (instance == nullptr) {
                // 初始化单例对象
                instance = new Singleton();

                // 设置单例对象
                _singleton.store(instance, memory_order_release);
            }
        }
        return instance;
    }

    // 销毁单例对象
    static void destroyInstance() {
        // 获取互斥锁
        lock_guard<mutex> lock(_mutex);

        // 释放资源
        Singleton *instance = _singleton.exchange(nullptr);
        if (instance != nullptr) {
            delete instance;
        }
    }

private:
    static mutex _mutex;                     // 声明静态变量（互斥锁）
    static atomic<Singleton *> _singleton;   // 声明静态变量（单例对象）

};

// 初始化静态变量（互斥锁）
mutex Singleton::_mutex;

// 初始化静态变量（单例对象）
atomic<Singleton *> Singleton::_singleton(nullptr);

int main() {
    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();
    cout << (s1 == s2 ? "true" : "false") << endl;

    return 0;
}
