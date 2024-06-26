/**
 * 函数模板与普通函数的区别以及调用规则
 *
 * (a) 函数模板不允许自动类型转换，普通函数能够进行自动类型转换。
 * (b) 当函数模板和普通函数都符合调用时，C++ 编译器优先选择调用普通函数
 * (c) 如果函数模板可以产生一个更好的匹配，那么 C++ 编译器会选择调用函数模板
 * (d) 如何希望强制调用函数模板，可以使用空模板实参列表（空参数列表）的语法来限制 C++ 编译器只使用函数模板匹配，比如 mySwap<>(a, b)
 */

#include <iostream>

using namespace std;

// 函数模板
template<class T>
T add(T x, T y) {
    cout << "函数模板被调用" << endl;
    return x + y;
}

// 普通函数
int add(int x, char y) {
    cout << "普通函数被调用" << endl;
    return x + y;
}

int main() {
    int x = 3;
    char c = 'a';

    add(x, c);      // 调用普通函数
    add(c, x);      // 调用普通函数，会进行隐式类型转换
    add(x, x);      // 调用函数模板（本质是类型参数化），将严格地按照类型进行匹配，不会进行隐式类型转换
    add<>(x, x);    // 强制调用函数模板，可以使用空模板实参列表的语法来限制 C++ 编译器只使用函数模板匹配
    return 0;
}
