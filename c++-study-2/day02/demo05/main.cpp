/**
 * 1. 函数重载
 *
 * <p> 用同一个函数名定义不同的函数
 * <p> 当函数名和不同的参数搭配时函数的含义不同
 * <p> 函数重载至少满足右边的一个条件：同一个作用域、参数个数不同、参数类型不同、参数顺序不同
 */

#include <iostream>

using namespace std;

void func(int a) {
    cout << "a = " << a << endl;
}

void func(int a, int b) {
    cout << "a = " << a << ", b = " << b << endl;
}

int main() {
    func(1);
    func(2, 3);
    return 0;
}