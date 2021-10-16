/**
 * 1. C++ 对 C 语言的增强
 */

#include <iostream>

using namespace std;

int main() {
    int a = 10;
    int b = 20;

    // 返回一个最小数，并且给最小数赋值成30
    // C 语言中三目运算符是一个表达式 ，表达式不可以做左值，而 C++ 则可以
    (a < b ? a : b) = 30;
    printf("a = %d, b = %d\n", a, b);
    return 0;
}
