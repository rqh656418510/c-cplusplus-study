/**
 * 可调用对象、std function、std bind
 *
 * (a) 可被转换为函数指针的类对象（函数对象 / 仿函数）
 */

#include <iostream>

void func1(int a) {
    std::cout << "void func1(int a)" << std::endl;
}

// 函数对象（仿函数）
class MyClass {
public:
    void operator()(int val) const {
        std::cout << "void operator()(int val)" << std::endl;
    }
};

// 可调用对象
class MyClass2 {
public:
    // 定义一个函数指针类型
    using fpoint = void (*)(int);

    // 静态成员函数
    static void process(int val) {
        std::cout << "void process(int val)" << std::endl;
    }

    operator fpoint() {
        return process;
    }
};

void test01() {
    // 声明函数指针
    void (*p)(int) = func1;

    // 通过函数指针调用函数
    p(3);
}

void test02() {
    // 声明函数对象
    MyClass mc;

    // 调用函数对象
    mc(5);
}

void test03() {
    MyClass2 mc2;
    mc2(5);
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}