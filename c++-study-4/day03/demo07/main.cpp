/**
 * 模板概念，函数模板定义、调用
 *
 * (a) 函数模板
 */

#include <iostream>

using namespace std;

// 定义函数模板
template<typename T>
T sum(T i1, T i2) {
    return i1 + i2;
}

void test01() {
    int total1 = sum(1, 3);
    cout << total1 << endl;

    double total2 = sum(3.4, 5.8);
    cout << total2 << endl;
}

int main() {
    test01();
    return 0;
}