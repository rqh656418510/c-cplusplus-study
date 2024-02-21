/**
 * 1. C++中的引用之常量引用（使用变量初始化 const 引用）
 */

#include <iostream>

using namespace std;

int main() {
    int a = 10;
    const int &b = a;
    // b = 11;  是错误写法，这里不能通过引用改变a的值，无法通过编译

    // 只能用指针来改变引用的值
    int * p = (int*) &b;
    *p = 11;

    printf("a:%d\n", a);
    printf("b:%d\n", b);
    printf("&a:%d\n", &a);
    printf("&b:%d\n", &b);
    return 0;
}

