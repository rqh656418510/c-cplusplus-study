/**
 * 1. C++中的函数重载
 */

#include <iostream>
#include <string.h>

using namespace std;

int func(int x) {
    return x;
}

int func(int a, int b) {
    return a + b;
}

int func(const char *s) {
    return strlen(s);
}

int main() {
    int c = 0;

    c = func(1);
    printf("c = %d\n", c);

    c = func(1, 2);
    printf("c = %d\n", c);

    c = func("12345");
    printf("c = %d\n", c);

    return 0;
}