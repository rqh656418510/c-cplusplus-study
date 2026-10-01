/**
 * 函数调用运算符、function类模板
 *
 * (b) function 类模板
 */

#include <functional>
#include <iostream>
#include <string>
#include <vector>

// 普通函数
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

// 接受 std::function 作为参数的函数
int compute(int x, int y, std::function<int(int, int)> op) {
    return op(x, y);
}

int main() {
    // 1. 用 std::function 包装普通函数
    std::function<int(int, int)> f = add;
    std::cout << "f(3, 4) = " << f(3, 4) << std::endl;

    // 2. 重新赋值为另一个普通函数
    f = subtract;
    std::cout << "f(10, 4) = " << f(10, 4) << std::endl;

    // 3. 作为函数参数传递（回调）
    std::cout << "compute(5, 6, add) = " << compute(5, 6, add) << std::endl;
    std::cout << "compute(5, 6, multiply) = " << compute(5, 6, multiply) << std::endl;

    // 4. 将普通函数存入容器，实现分派表
    std::vector<std::function<int(int, int)>> ops = {add, subtract, multiply};
    std::vector<std::string> names = {"add", "subtract", "multiply"};
    for (size_t i = 0; i < ops.size(); ++i) {
        std::cout << names[i] << "(8, 2) = " << ops[i](8, 2) << std::endl;
    }

    // 5. 空 std::function 检查
    std::function<int(int, int)> g;
    if (!g) {
        std::cout << "g is empty" << std::endl;
    }
    g = add;
    if (g) {
        std::cout << "g(1, 2) = " << g(1, 2) << std::endl;
    }

    return 0;
}
