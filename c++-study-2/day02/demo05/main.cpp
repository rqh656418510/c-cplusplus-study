/**
 * 1. 函数重载
 *
 * <p> 用同一个函数名定义不同的函数
 * <p> 当函数名和不同的参数搭配时函数的含义不同
 * <p> 函数重载至少满足右边的一个条件：同一个作用域、参数个数不同、参数类型不同、参数顺序不同
 * <p> 当函数重载遇上引用时，`const` 关键字也是可以作为函数重载的条件
 */

#include <iostream>

using namespace std;

void funcA(int a) {
    cout << "a = " << a << endl;
}

void funcA(int a, int b) {
    cout << "a = " << a << ", b = " << b << endl;
}

// 引用必须要引一块合法的内存空间，这里使用 funcB(10) 调用函数是非法的
void funcB(int &a) {
    cout << "a = " << a << endl;
}

// 加上 const 关键字后，这里使用 funcB(10) 调用函数是合法的
void funcB(const int &a) {
    int sum = a + 3;
    cout << "sum = " << sum << endl;
}

int main() {
    funcA(1);
    funcA(2, 3);
    funcB(3);
    return 0;
}