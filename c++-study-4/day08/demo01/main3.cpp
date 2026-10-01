/**
 * 函数调用运算符、function类模板
 *
 * (c) 函数指针
 */

#include <iostream>

// 定义几个普通函数
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

// 接受函数指针作为参数的函数（回调函数）
int compute(int x, int y, int (*op)(int, int)) {
    return op(x, y);
}

int main() {
    // 声明并初始化函数指针
    int (*p)(int, int) = add;

    // 通过函数指针调用
    std::cout << "p(3, 4) = " << p(3, 4) << std::endl;        // 输出 7
    std::cout << "(*p)(3, 4) = " << (*p)(3, 4) << std::endl;  // 输出 7

    // 让函数指针指向另一个函数
    p = subtract;
    std::cout << "p(10, 4) = " << p(10, 4) << std::endl;  // 输出 6

    // 将函数指针作为参数传递（回调）
    std::cout << "compute(5, 6, add) = " << compute(5, 6, add) << std::endl;            // 输出 11
    std::cout << "compute(5, 6, multiply) = " << compute(5, 6, multiply) << std::endl;  // 输出 30

    // 用函数指针数组实现简单的 "分派表"
    int (*ops[])(int, int) = {add, subtract, multiply};
    for (int i = 0; i < 3; ++i) {
        std::cout << "ops[" << i << "](8, 2) = " << ops[i](8, 2) << std::endl;
    }
    // 输出：10, 6, 16

    return 0;
}