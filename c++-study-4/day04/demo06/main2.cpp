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
}

int main() {
    test01();
    test02();
    test03();
    test04();
    return 0;
}