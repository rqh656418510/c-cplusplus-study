/**
 * weak_ptr概述、weak_ptr常用操作、尺寸
 *
 * (a) weak_ptr 的常用操作
 */

#include <iostream>
#include <memory>

using namespace std;

// lock()
void test01() {
    shared_ptr<int> sp = make_shared<int>(100);
    weak_ptr<int> wp(sp);

    shared_ptr<int> sp2 = wp.lock();
    if (sp2 != nullptr) {
        cout << "object value is " << *sp2 << endl;
    } else {
        cout << "object not exist" << endl;
    }
}

// lock()
void test02() {
    shared_ptr<int> sp = make_shared<int>(100);
    weak_ptr<int> wp(sp);

    // 释放 shared_ptr 所管理的对象
    sp.reset();

    shared_ptr<int> sp2 = wp.lock();
    if (sp2 != nullptr) {
        cout << "object value is " << *sp2 << endl;
    } else {
        cout << "object not exist" << endl;
    }
}

// use_count()
void test03() {
    shared_ptr<int> sp = make_shared<int>(100);
    weak_ptr<int> wp(sp);
    int count = wp.use_count();
    cout << count << endl;
}

// use_count()
void test04() {
    shared_ptr<int> sp = make_shared<int>(100);
    weak_ptr<int> wp(sp);

    // 释放 shared_ptr 所管理的对象
    sp.reset();

    int count = wp.use_count();
    cout << count << endl;
}

// expired()
void test05() {
    shared_ptr<int> sp = make_shared<int>(100);
    weak_ptr<int> wp(sp);
    bool expired = wp.expired();
    cout << expired << endl;  // 输出 0，表示 false（未过期）
}

// expired()
void test06() {
    shared_ptr<int> sp = make_shared<int>(100);
    weak_ptr<int> wp(sp);

    // 释放 shared_ptr 所管理的对象
    sp.reset();

    bool expired = wp.expired();
    cout << expired << endl;  // 输出 1，表示 true（已过期）
}

// reset()
void test07() {
    shared_ptr<int> sp = make_shared<int>(100);
    weak_ptr<int> wp(sp);

    // 将 `weak_ptr` 设置为空指针，不影响所指向对象的强引用计数（即 `shared_ptr` 所指向对象的引用计数）
    wp.reset();
}

// 指针大小问题
void test08() {
    weak_ptr<int> wp;
    int *p;
    int length1 = sizeof(p);   // 8 个字节（64 位系统）
    int length2 = sizeof(wp);  // 16 个字节（64 位系统）
    cout << "length1 = " << length1 << endl;
    cout << "length2 = " << length2 << endl;
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
    return 0;
}