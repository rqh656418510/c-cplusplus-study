/**
 * 1. 内联函数的使用
 */

#include <iostream>

using namespace std;

// 宏函数定义
#define MY_ADD(x, y) ((x) + (y))

// 宏函数定义
#define MY_COMPARE(a, b) ((a) < (b) ? (a) : (b))

// 内联函数定义
inline double my_div(double a, double b) {
    return a / b;
}

// 宏函数使用
void test01() {
    int sum = MY_ADD(1, 2);
    cout << "sum = " << sum << endl;
}

// 宏函数使用
void test02() {
    int a = 10;
    int b = 20;
    int result = MY_COMPARE(a, b);
    cout << "result = " << result << endl;
}

// 内联函数调用
void test03() {
    int a = 30;
    int b = 7;
    double result = my_div(a, b);
    cout << "result = " << result << endl;
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}