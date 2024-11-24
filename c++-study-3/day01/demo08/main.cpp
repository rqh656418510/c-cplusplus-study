/**
 * 掌握C++的左值引用和初识右值引用
 */

#include <iostream>

using namespace std;

/**
 * 指针与引用
 */
void test01() {
    int a = 10;
    int *p = &a;
    int &b = a; // 引用，其底层是基于指针实现的
    // int &c = 20; // 错误写法

    *p = 20;
    cout << a << " " << *p << " " << b << endl; // 20 20 20

    b = 30;
    cout << a << " " << *p << " " << b << endl; // 30 30 30
}

void swap1(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap2(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

/**
 * 指针与引用
 */
void test02() {
    int a = 10;
    int b = 20;
    // swap1(&a, &b);
    swap2(a, b);
    cout << "a = " << a << ", b = " << b << endl;   // a = 20, b = 10
}

/**
 * 引用数组变量
 */
void test03() {
    int array[5] = {};
    int *p = array;
    cout << sizeof(array) << endl;  // 20
    cout << sizeof(p) << endl;  // 4

    // 定义一个引用变量来引用数组变量
    int (&q)[5] = array;
    cout << sizeof(q) << endl; // 20
}

/**
 * 左值引用与右值引用
 */
void test04() {
    int a = 10; // 左值，它有内存，有名称，值可以修改
    int &b = a; // 左值引用
    cout << "b = " << b << endl; // b = 10

    // int &c = 20; // 错误写法，左值引用只能引用左值，20 是右值（没有内存和名称），不能引用 20
    int &&c = 20; // 正确写法，C++ 提供了右值引用
    // int &&c = a; // 错误写法，右值引用只能引用右值，a 是左值，不能引用 a
    cout << "c = " << c << endl; // c = 20
}

int main() {
    test01();
    test02();
    test03();
    test04();
    return 0;
}
