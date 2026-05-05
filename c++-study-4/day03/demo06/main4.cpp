/**
 * 类成员指针
 *
 * (d) 类成员变量指针
 */

#include <iostream>

using namespace std;

class MyTest {
public:
    int m_common = 0;     // 普通成员变量
    static int m_static;  // 静态成员变量
};

// 初始化静态成员变量
int MyTest::m_static = 0;

void test01() {
    // 针对普通成员变量定义一个类成员变量指针，本质并不是指向内存中的某个地址，而是该类成员变量与该类对象指针之间的地址偏移量
    int MyTest::*ptr1 = &MyTest::m_common;

    // 通过对象本身 + 类成员变量指针修改普通成员变量的值
    MyTest t1;
    t1.*ptr1 = 20;
    cout << "address: " << ptr1 << ", value: " << t1.m_common << endl;
}

void test02() {
    // 针对静态成员变量定义一个类成员变量指针，指向的是真正的内存地址
    int *ptr1 = &MyTest::m_static;

    // 直接通过类成员变量指针修改静态成员变量的值，等价于 MyTest::m_static = 40
    *ptr1 = 40;
    cout << "address: " << ptr1 << ", value: " << *ptr1 << endl;
}

int main() {
    test01();
    test02();
    return 0;
}