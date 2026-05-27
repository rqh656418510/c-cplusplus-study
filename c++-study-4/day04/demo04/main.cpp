/**
 * weak_ptr概述、weak_ptr常用操作、尺寸
 *
 * (a) weak_ptr 的创建
 */

#include <iostream>
#include <memory>

using namespace std;

// weak_ptr 的创建
void test01() {
    // 直接使用 shared_ptr 来初始化 weak_ptr
    shared_ptr<int> sp = make_shared<int>(100);
    weak_ptr<int> wp(sp);
}

// weak_ptr 的创建
void test02() {
    // 或者将 shared_ptr 赋值给 weak_ptr
    shared_ptr<int> sp = make_shared<int>(100);
    weak_ptr<int> wp;
    wp = sp;
}

// weak_ptr 的创建
void test03() {
    // 或者将 weak_ptr 赋值给 weak_ptr
    shared_ptr<int> sp = make_shared<int>(100);
    weak_ptr<int> wp(sp);
    weak_ptr<int> wp2;
    wp2 = wp;
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}