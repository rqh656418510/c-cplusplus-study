/**
 * Lambda 表达式捕获模式的陷阱分析和展示
 *
 * (c) Lambda 表达式使用陷阱 - 静态局部变量
 */

#include <functional>
#include <iostream>
#include <vector>

std::vector<std::function<bool(int)>> vec;

void process() {
    // 静态局部变量
    static int num = 3;

    // Lambda 表达式无法捕获静态局部变量，但可以直接使用，效果相当于按引用捕获，而不是按值捕获
    vec.push_back([](const int val) {
        std::cout << "num = " << num << std::endl;  // 输出 4
        return val % num == 0;
    });

    num++;
}

int main() {
    process();
    int result = vec[0](5);
    std::cout << result << std::endl;
    return 0;
}