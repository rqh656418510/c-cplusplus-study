/**
 * 函数新特性、内联函数、const详解
 */

#include <iostream>

using namespace std;

// 未命名参数
int func1(int a, int) {
    return a * 2;
}

// 后置返回类型
auto func2(int a, int b) -> int {
    return a + b;
}

int main() {
    func1(1, 3);
    func2(2, 4);
}