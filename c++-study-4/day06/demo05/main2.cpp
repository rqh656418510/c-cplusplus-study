/**
 * 重载全局new、delete，定位new及重载等
 *
 * (b) 定位 new（placement new）
 */

#include <iostream>

class MyClass {

public:
    MyClass() : m_a(0) {
        std::cout << "MyClass::MyClass()" << std::endl;
    }

    MyClass(const int val) : m_a(val) {
        std::cout << "MyClass::MyClass(const int val)" << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass::~MyClass()" << std::endl;
    }

private:
    int m_a;
};

int main() {
    // 预先分配内存
    void *ptr = (void *)new char[sizeof(MyClass)];

    // 定位 new，会调用无参构造函数
    MyClass *mc = new (ptr) MyClass();

    // 或者，定位 new，调用有参构造函数
    // MyClass *mc = new (ptr) MyClass(2);

    // 显示调用析构函数
    mc->~MyClass();

    // 释放原始内存
    delete[] (char *)ptr;

    return 0;
}