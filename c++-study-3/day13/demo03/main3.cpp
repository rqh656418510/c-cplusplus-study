/**
 * 单例模式代码设计
 */

#include <iostream>

// 懒汉单例模式（线程安全），基于 C++ 11 局部静态变量的线程安全初始化特性

using namespace std;

class Singleton {

public:
    static Singleton &getInstance() {
        static Singleton instance;
        return instance;
    }

    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

private:
    Singleton() = default;

};

int main() {
    Singleton &s1 = Singleton::getInstance();
    Singleton &s2 = Singleton::getInstance();
    cout << (&s1 == &s2 ? "true" : "false") << endl;
    return 0;
}
