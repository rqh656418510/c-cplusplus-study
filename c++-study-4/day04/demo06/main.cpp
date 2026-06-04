/**
 * unique_ptr概述、常用操作
 *
 * (a) unique_ptr 的初始化
 */

#include <iostream>
#include <memory>

using namespace std;

// unique_ptr 的初始化
void test01() {
    // unique_ptr 空指针
    unique_ptr<int> up1;

    // 直接初始化 unique_ptr
    unique_ptr<int> up2(new int(100));

    // C++ 14 开始支持 make_unique() 函数模板
    // unique_ptr<int> up3 = make_unique<int>();

    // 使用裸指针初始化 unique_ptr（不推荐）
    int *pi = new int(100);
    unique_ptr<int> upi(pi);
}

// unique_ptr 不支持的操作
void test02() {
    unique_ptr<int> up1(new int(100));
    // unique_ptr<int> up2(up1);   // 错误写法（编译失败），unique_ptr 是独占式的，不支持拷贝构造函数
    // unique_ptr<int> up2 = up1;  // 错误写法（编译失败），unique_ptr 是独占式的，不支持拷贝构造函数

    unique_ptr<int> up3;
    // up3 = up1; // 错误写法（编译失败），unique_ptr 是独占式的，不支持拷贝赋值运算符
}

int main() {
    test01();
    test02();
    return 0;
}