/**
 * 1. C++中的函数占位参数
 */

#include <iostream>

using namespace std;

int func(int a, int b, int) {
    return a + b;
}

int main() {
    printf("func(1, 2, 3) = %d\n", func(1, 2, 3));
    return 0;
}