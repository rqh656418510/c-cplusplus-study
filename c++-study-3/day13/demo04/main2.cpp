/**
 * 线程安全的懒汉单例模式
 */

#include <iostream>

// 懒汉单例模式（线程安全），基于 C++ 11 局部静态变量的线程安全初始化特性

using namespace std;

class Singleton {

private:
    // 私有的默认构造函数
    Singleton() {

    }

    // 删除拷贝构造函数
    Singleton(const Singleton &) = delete;

    // 删除赋值运算符
    Singleton &operator=(const Singleton &) = delete;

public:

    // 获取单例对象
    static Singleton *getInstance() {
        // 局部静态变量
        static Singleton instance;

        return &instance;
    }

};

int main() {
    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();
    cout << (s1 == s2 ? "true" : "false") << endl;
    return 0;
}
