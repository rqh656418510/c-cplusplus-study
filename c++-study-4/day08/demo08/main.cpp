/**
 * lambda表达式，for_each、find_if简介
 *
 * (a) Lambda 表达式使用
 */

#include <iostream>

int main() {
    auto f1 = [](const int a, const int b) -> int { return a + b; };
    int r1 = f1(2, 3);
    std::cout << "r1: " << r1 << std::endl;
    return 0;
}