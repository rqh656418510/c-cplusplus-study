/**
 * 全面掌握const的用法
 */

#include <iostream>

using namespace std;

void test01() {
    // 用字面量常量初始化常量
    const int a = 3;

    // 在 C++ 中，常量可以作为数组大小，因为 C++ 中 const 常量是在编译时确定的
    int array[a] = {};

    // 在 C++ 中，不可以通过操作指针的方式来修改 const 变量的值
    // 当使用 & 操作符取 const 常量的地址时，编译器会临时开辟一块内存空间
    int *p = (int *) &a;
    *p = 20;
    printf("%d %d %d\n", a, *p, *(&a)); // 3 20 3
}

void test02() {
    int a = 20;
    // 用变量来初始化常量（通常叫常变量）
    const int b = a;

    // 此时不能再用来作为数组大小
    // int array[b] = {};

    // 此时可以通过操作指针的方式来修改 const 变量的值
    int *p = (int *) &a;
    *p = 20;
    printf("%d %d %d\n", a, *p, *(&a)); // 20 20 20
}

int main() {
    test01();
    test02();
    return 0;
}
