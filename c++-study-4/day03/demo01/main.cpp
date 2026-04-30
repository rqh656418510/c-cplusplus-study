/**
 * 左值、右值、左值引用、右值引用、move
 */

#include <iostream>

using namespace std;

// 三种形式的引用
void test01() {
    // 左值引用（绑定到左值）
    int value = 10;
    int &refval = value;
    refval = 20;

    // 常量引用，也是左值引用（绑定到左值）
    const int &refval2 = value;

    // 常量引用，也可以是右值引用（绑定到右值）
    const int &refval3 = 3;

    // 右值引用（绑定到右值）
    int &&refval4 = 30;
    refval4 = 35;
}

// 前置运算符和后置运算符
void test02() {
    int i = 1;

    // 左值引用（绑定到左值），前置 ++、前置 -- 返回的是左值表达式
    int &refval = ++i;

    // 右值引用（绑定到右边值），后置 ++、后置 -- 返回的是右值表达式
    int &&refval2 = i++;
}

int main() {
    test01();
    test02();
    return 0;
}