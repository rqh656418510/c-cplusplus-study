/**
 * 掌握inline内联函数
 */

#include <iostream>

using namespace std;

// 定义内联函数
inline int sum(int a, int b) {
    return a + b;
}

int main() {
    int a = 10;
    int b = 20;
    int result = sum(a, b);
    return 0;
}
