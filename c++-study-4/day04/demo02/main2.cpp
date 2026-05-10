/**
 * new、delete探秘，智能指针概述、shared_ptr
 *
 * (b) 基于 new 如何记录分配的内存大小供 delete 使用
 */

#include <iostream>
#include <memory>

using namespace std;

class MyClass {
public:
    // 构造函数
    MyClass() {
        cout << "MyClass() called" << endl;
    }

    // 析构函数
    ~MyClass() {
        cout << "~MyClass() called" << endl;
    }
};

void test01() {
    cout << "---------- test01() ----------" << endl;

    // 空类（不包含任何成员变量）占一个字节大小
    MyClass mc;
    size_t len = sizeof(mc);
    cout << "size: " << len << endl;  // 输出 1
}

void test02() {
    // 分配整型数组
    int* iarray = new int[2];

    // 释放整型数组，如果这里不执行 delete[]，会泄露 16 个字节内存
    delete[] iarray;
}

void test03() {
    cout << "---------- test03() ----------" << endl;

    // 分配对象数组
    MyClass* parray = new MyClass[2];

    // 释放对象数组，如果这里不执行 delete[]，会泄露 18 个字节内存（不同平台有差异）
    delete[] parray;
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}