/**
 * 1. C++中的默认参数
 */

#include <iostream>

using namespace std;

void funcA(int x = 3) {
    printf("x: %d\n", x);
}

void funcB(int a, int b, int y = 4, int z = 5) {
    printf("a: %d, b: %d, y: %d, z: %d\n", a, b, y, z);
}

int main() {
    funcA();
    funcA(6);
    funcB(1, 2);
    funcB(1, 2, 3, 4);
    return 0;
}