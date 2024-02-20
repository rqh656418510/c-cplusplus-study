/**
 * 1. C++ 中引用作函数参数
 */

#include <iostream>

using namespace std;

// 指针作函数参数
void mySwap1(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 引用作函数参数
void mySwap2(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// 使用指针交换两个变量的值
void test01() {
    int a = 10, b = 20;
    mySwap1(&a, &b);
    cout << "a = " << a << ", b = " << b << endl;
}

// 使用引用交换两个变量的值
void test02() {
    int a = 50, b = 60;
    mySwap2(a, b);
    cout << "a = " << a << ", b = " << b << endl;
}

int main() {
    test01();
    test02();
    return 0;
}