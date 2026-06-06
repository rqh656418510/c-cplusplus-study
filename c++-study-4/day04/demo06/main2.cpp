/**
 * unique_ptr概述、常用操作
 *
 * (b) unique_ptr 的常用操作
 */

#include <iostream>
#include <memory>

using namespace std;

// 移动语义的支持
void test01() {
    unique_ptr<int> up1(new int(100));
    unique_ptr<int> up2 = move(up1);  // 移动完成后，up1 置为空指针，up2 指向 up1 原来所指向的对象
}

// release()
void test02() {
    unique_ptr<int> up1(new int(100));
    int* p = up1.release();  // 释放完成后，up1 置为空指针
    unique_ptr<int> up2(p);  // up2 指向 up1 原来所指向的对象，不会发生内存泄漏
}

// reset()
void test03() {
    // 情况一（不带参数）
    unique_ptr<int> up1(new int(100));
    up1.reset();  // up1 所指向对象的内存会被释放，up1 置为空指针

    // 情况二（带参数）
    unique_ptr<int> up2(new int(100));
    int* p = new int(200);
    up2.reset(p);  // up2 原来所指向对象的内存会被释放，up2 指向最新的对象 p
}

// = nullptr
void test04() {
    unique_ptr<int> up(new int(100));
    up = nullptr;  // up 所指向对象的内存会被释放，up 置为空指针
}

// 自定义类（带自定义的析构函数）
class MyClass {
public:
    MyClass() {
    }
    ~MyClass() {
        cout << "~MyClass()" << endl;
    }
};

// 指向数组
void test05() {
    // 从 C++ 17 开始正式支持以下写法，使用数组特化版本 unique_ptr<T[]>，可以正确释放数组内存
    unique_ptr<MyClass[]> up(new MyClass[3]);
}

// get()
void test06() {
    unique_ptr<int> sp(new int(100));
    int* p = sp.get();
    *p = 50;
    cout << *p << endl;  // 输出 50
}

// * 解引用
void test07() {
    unique_ptr<int> sp(new int(100));
    cout << *sp << endl;  // 输出 100
}

// swap()
void test08() {
    unique_ptr<int> up1(new int(100));
    unique_ptr<int> up2(new int(200));
    up1.swap(up2);  // 交换两个智能指针指向的对象
}

// 智能指针名称作为判断条件
void test09() {
    unique_ptr<int> up(new int(100));
    if (up != nullptr) {
        cout << "not nullptr" << endl;  // 执行输出
    }

    up.reset();
    if (up != nullptr) {
        cout << "not nullptr" << endl;
    } else {
        cout << "nullptr" << endl;  // 执行输出
    }
}

unique_ptr<int> func() {
    return unique_ptr<int>(new int(100));  // 返回一个右值（临时对象都是右值）
}

// 转换为 shared_ptr 类型
void test10() {
    shared_ptr<int> sp = func();  // 这里会额外创建一个控制块（用于存储引用计数、删除器等）
}

// 转换为 shared_ptr 类型
void test11() {
    unique_ptr<int> up(new int(100));
    shared_ptr<int> sp = move(up);  // 将左值转换为右值
                                    // 移动完成后，up 置为空指针，sp 指向 up 原来所指向的对象
}

int main() {
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
    test07();
    test08();
    test09();
    test10();
    test11();
    return 0;
}