/**
 * 单例设计模式共享数据分析、解决，call_once
 *
 * (a) 单例设计模式使用 - 饿汉单例模式
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
    MyClass& operator=(const MyClass&) = delete;

public:
    // 获取单例对象（静态方法）
    static MyClass* getInstance() {
        return m_instance;
    }

private:
    // 静态成员变量
    static MyClass* m_instance;
};

// 类外初始化静态变量（单例对象），分配内存空间
MyClass* MyClass::m_instance = new MyClass();

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