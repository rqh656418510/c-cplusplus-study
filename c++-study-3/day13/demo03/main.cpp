/**
 * 单例模式代码设计
 */

#include <iostream>

// 饿汉单例模式

using namespace std;

class Singleton {

private:
    // 私有的默认构造函数
    Singleton() {

    }

    // 删除拷贝造函数
    Singleton(const Singleton &) = delete;

    // 删除赋值运算符
    Singleton &operator=(const Singleton &) = delete;

public:
    // 获取单例
    static Singleton *getInstance() {
        return singleton;
    }

private:
    // 声明静态变量（单例）
    static Singleton *singleton;

};

// 初始化静态变量（单例），分配内存空间
Singleton *Singleton::singleton = new Singleton();

int main() {
    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();
    cout << (s1 == s2 ? "true" : "false") << endl;

    return 0;
}
