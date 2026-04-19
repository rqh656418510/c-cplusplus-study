/**
 * using定义别名模板，显式指定模板参数
 *
 * (c) using定义别名模板 + 函数指针
 */

#include <iostream>

using namespace std;

// 定义别名模板 + 函数指针
template <typename T>
using funcType = T (*)(T, T);

int sum(int a, int b) {
    return a + b;
}

int main() {
    // 定义函数指针
    funcType<int> func;  // funcType 是一个函数指针类型，func 是函数指针变量

    // 将函数地址赋值给函数指针变量
    func = sum;

    // 调用函数指针
    int result = func(1, 3);
    cout << result << endl;

    return 0;
}