/**
 * 1. C++�еĺ���ռλ����
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