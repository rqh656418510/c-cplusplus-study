/**
 * 函数模板与函数重载
 *
 * (a) 函数模板可以像普通函数一样被重载
 * (b) 如何出现重载，C++ 编译器优先选择调用普通函数
 * (c) 如果函数模板可以产生一个更好的匹配，那么 C++ 编译器会选择调用函数模板
 * (d) 如何希望强制调用函数模板，可以使用空模板实参列表（空参数列表）的语法来限制 C++ 编译器只使用函数模板匹配，比如 mySwap<>(a, b)
 */

#include <iostream>

using namespace std;

// 普通函数
int Max(int a, int b) {
    cout << "int Max(int a, int b)" << endl;
    return a > b ? a : b;
}

// 函数模板
template<typename T>
T Max(T a, T b) {
    cout << "T Max(T a, T b)" << endl;
    return a > b ? a : b;
}

// 函数模板重载
template<typename T>
T Max(T a, T b, T c) {
    cout << "T Max(T a, T b, T c)" << endl;
    return Max(Max(a, b), c);
}

int main() {
    int a = 1;
    int b = 2;

    Max(a, b); // 当函数模板和普通函数都符合调用时，优先选择调用普通函数
    Max('a', 100);  // 调用普通函数，可以进行隐式类型转换
    Max<>(a, b); // 通过空模板实参列表的语法，可以限制编译器只使用函数模板匹配
    Max(3.0, 4.0); // 如果函数模板产生更好的匹配，编译器会使用函数模板

    cout << "--------------------" << endl;

    Max(5.0, 6.0, 7.0); // 函数模板的重载

    return 0;
}
