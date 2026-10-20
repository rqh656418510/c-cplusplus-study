/**
 * lambda表达式，for_each、find_if简介
 *
 * (a) Lambda 表达式使用
 */

#include <iostream>

// 基础用法
void test01() {
    std::cout << "--------------- test01() ---------------" << std::endl;
    auto f1 = [](const int a, const int b) -> int { return a + b; };
    int r1 = f1(2, 3);
    std::cout << "r1: " << r1 << std::endl;

    auto f2 = []() {};
    auto f3 = [] {};
}

// 捕获方式
void test02() {
    std::cout << "--------------- test02() ---------------" << std::endl;
    int a = 10;
    int b = 20;
    int c = 30;

    // 按值捕获
    auto f1 = [a] { std::cout << "a: " << a << std::endl; };
    f1();

    // 按引用捕获
    auto f2 = [&b] { std::cout << "b: " << b++ << std::endl; };
    f2();
    std::cout << "b = " << b << std::endl;

    // 按引用捕获
    auto f3 = [&c] { std::cout << "c: " << c++ << std::endl; };
    f3();
    std::cout << "c = " << c << std::endl;
}

// 直接使用静态局部变量
void test03() {
    std::cout << "--------------- test03() ---------------" << std::endl;
    static int a = 10;
    auto f1 = [] { std::cout << "a: " << a << std::endl; };
    f1();
}

void test04() {
    std::cout << "--------------- test04() ---------------" << std::endl;
}

int main() {
    test01();
    test02();
    test03();
    test04();
    return 0;
}