/**
 * 1. C++中的函数重载与函数默认参数
 */

#include <iostream>

using namespace std;

int func(int a, int b, int c = 0) {
    return a * b * c;
}

int func(int a, int b) {
    return a + b;
}

int func(int a) {
    return a;
}

int main() {
    int c = 0;
    // c = func(1, 2); // 存在二义性，调用失败，编译不能通过
    printf("c = %d\n", c);
    return 0;
}