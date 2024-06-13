/**
 * 函数模板的基础使用
 */

#include <iostream>

using namespace std;

// 模板声明
template<class T>

// 函数定义
void mySwap(T &t1, T &t2) {
    T tmp = t1;
    t1 = t2;
    t2 = tmp;
}

int main() {
    // 自动数据类型推导
    int x = 3, y = 5;
    mySwap(x, y);
    cout << "x = " << x << ", y = " << y << endl;

    // 自动数据类型推导
    double m = 1.2, n = 5.6;
    mySwap(m, n);
    cout << "m = " << m << ", n = " << n << endl;

    // 显式指定类型调用（推荐）
    char c1 = 'A', c2 = 'B';
    mySwap<char>(c1, c2);
    cout << "c1 = " << c1 << ", c2 = " << c2 << endl;

    return 0;
}
