/**
 * 模板概念，函数模板定义、调用
 *
 * (a) 函数模板定义
 */

#include <iostream>

using namespace std;

// 定义函数模板
template <typename T>
T maxNum(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    // 调用时，编译器根据实参(10, 20)推断 T 为 int
    int result1 = maxNum(10, 20);

    // 调用时，编译器根据实参(3.14, 2.71)推断 T 为 double
    double result2 = maxNum(3.14, 2.71);

    // 如果实参类型不一致，编译器无法唯一确定 T，会导致推断失败
    // double result3 = max(10, 3.14);

    // 显式指定模板参数
    double result3 = maxNum<double>(10, 3.14);

    return 0;
}