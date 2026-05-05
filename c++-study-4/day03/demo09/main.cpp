/**
 * typename场合、默认模板参数、趣味写法分析
 *
 * (a) 函数指针作为其他函数的参数
 */

#include <iostream>

using namespace std;

// 定义函数指针类型（第一种写法，C 语义风格）
typedef int (*FunType)(int, int);

// 定义函数指针类型（第二种写法，C++ 现代写法）
// using FunType = int(*)(int, int);

// 定义普通函数
int sum(int a, int b) {
    return a + b;
}

// 函数指针作为其他函数的参数
int testFunc(int i, int j, FunType func) {
    // 通过调用函数指针调用函数
    return func(i, j);
}

int main() {
    int result = testFunc(3, 5, sum);
    cout << result << endl;
    return 0;
}