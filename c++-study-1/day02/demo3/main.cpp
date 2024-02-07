/**
 * 1. C++中的内联函数
 */

#include <iostream>

using namespace std;

// 宏定义函数的声明
#define MAXFUNC(x, y) (x > y) ? x : y

// 内联函数的声明
inline int Max(int x, int y) {
    return (x > y) ? x : y;
}

int main() {
    // 内联函数的调用
    cout << "Max (20,10): " << Max(20, 10) << endl;
    cout << "Max (0,200): " << Max(0, 200) << endl;
    cout << "Max (100,1010): " << Max(100, 1010) << endl;

    // 宏定义函数的调用
    printf("Max (10,30): %d\n", MAXFUNC(10, 30));
    return 0;
}