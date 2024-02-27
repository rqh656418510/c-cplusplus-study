/**
 * 1. 函数默认参数与函数占位参数
 *
 * <p> 只有参数列表后面部分的参数才可以提供默认参数值
 * <p> 一旦在一个函数调用中开始使用默认参数值，那么这个参数后的所有参数都必须使用默认参数值
 * <p> 一旦在函数声明里面有了默认参数，那么函数实现的时候不能再有默认参数，也就是说，函数声明和函数实现两者只能有一个允许有函数默认参数
 */

#include <iostream>

using namespace std;

// 函数默认参数使用
void funcA(int a = 1, int b = 2) {
    cout << "a = " << a << ", b = " << b << endl;
}

// 函数默认参数使用
void funcB(int a, int b = 2, int c = 3) {
    cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
}

// 函数声明和函数实现两者只能有一个允许有函数默认参数
void funcC(int a, int b);

void funcC(int a, int b = 2) {
    cout << "a = " << a << ", b = " << b << endl;
}

// 函数占位参数使用
void funcD(int a, int b, int) {
    cout << "a = " << a << ", b = " << b << endl;
}

// 函数默认参数结合函数占位参数一起使用
void funcE(int a, int b, int = 0) {
    cout << "a = " << a << ", b = " << b << endl;
}

int main() {
    funcA();
    funcA(5);
    funcA(5, 6);

    funcB(1);
    funcB(1, 4);
    funcB(1, 4, 8);

    funcC(1, 3);

    funcD(3, 5, 7);

    funcE(8, 10);
    funcE(8, 10, 12);

    return 0;
}
