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

    // 右值引用（绑定到右值）
    int &&refval3 = 30;
    refval3 = 35;
}

int main() {
    test01();
    return 0;
}