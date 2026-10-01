/**
 * 函数调用运算符、function类模板
 *
 * (c) 函数指针
 */

#include <iostream>
#include <map>
#include <string>

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
    // 1. 声明并初始化函数指针
    int (*p)(int, int) = add;

    // 2. 通过函数指针调用
    std::cout << "p(3, 4) = " << p(3, 4) << std::endl;
    std::cout << "(*p)(3, 4) = " << (*p)(3, 4) << std::endl;

    // 3. 让函数指针指向另一个函数
    p = subtract;
    std::cout << "p(10, 4) = " << p(10, 4) << std::endl;

    // 4. 将函数指针作为参数传递（回调）
    std::cout << "compute(5, 6, add) = " << compute(5, 6, add) << std::endl;
    std::cout << "compute(5, 6, multiply) = " << compute(5, 6, multiply) << std::endl;

    // 5. 用函数指针数组实现简单的 "分派表"
    int (*ops[])(int, int) = {add, subtract, multiply};
    for (int i = 0; i < 3; ++i) {
        std::cout << "ops[" << i << "](8, 2) = " << ops[i](8, 2) << std::endl;
    }

    // 6. 将多个函数指针放入同一个容器
    std::map<std::string, int (*)(int, int)> container;
    container.insert(std::make_pair("add", ops[0]));
    container.insert(std::make_pair("subtract", ops[1]));
    container.insert(std::make_pair("multiply", ops[2]));
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << it->first << "(3, 4) = " << it->second(3, 4) << std::endl;
    }

    return 0;
}