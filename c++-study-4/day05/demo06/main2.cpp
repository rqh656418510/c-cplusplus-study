/**
 * 单例设计模式共享数据分析、解决，call_once
 *
 * (b) 单例设计模式使用 - 懒汉单例模式（基于静态局部变量）
 */

#include <iostream>
#include <thread>

using namespace std;

class MyClass {
private:
    // 私有构造函数
    MyClass() {
        cout << "MyClass()" << endl;
    }

    // 私有析构函数
    ~MyClass() {
        cout << "~MyClass()" << endl;
    }

    // 删除拷贝构造函数
    MyClass(const MyClass&) = delete;

    // 删除赋值操作运算符
    MyClass operator=(const MyClass&) = delete;

public:
    // 获取单例对象（静态方法）
    static MyClass* getInstance() {
        // 静态局部变量（线程安全）
        static MyClass instance;
        return &instance;
    }
};

int main() {
    // 获取单例对象
    MyClass* mc = MyClass::getInstance();
    MyClass* mc2 = MyClass::getInstance();

    // 判断地址是否相同
    cout << "address: " << mc << endl;
    cout << "address: " << mc2 << endl;
    cout << "equals: " << (mc == mc2 ? "true" : "false") << endl;

    return 0;
}