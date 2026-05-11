/**
 * new、delete探秘，智能指针概述、shared_ptr
 *
 * (c) shared_ptr 智能指针的使用
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

int main() {
    // 第一种写法
    shared_ptr<int> sp1(new int(100));
    shared_ptr<MyClass> sp2(new MyClass());

    // 第二种写法
    shared_ptr<int> sp3 = make_shared<int>(100);
    shared_ptr<MyClass> sp4 = make_shared<MyClass>();

    // 错误写法（不支持隐式类型转换）
    // shared_ptr<int> sp = new int(100);

    return 0;
}