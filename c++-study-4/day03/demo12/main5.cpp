/*
 * 模板全特化、偏特化(局部特化)
 *
 * (e) 函数模板全特化
 */

#include <iostream>

using namespace std;

// 定义函数模板（泛化版本）
template <typename T, typename U>
void func(T t, U u) {
    cout << "func(T, U) 泛化版本" << endl;
}

// 定义函数模板（全特化版本）
template <>
void func(int t, int u) {
    cout << "func(int, int) 全特化版本" << endl;
}

// 定义函数模板（全特化版本）
template <>
void func(double t, double u) {
    cout << "func(double, double) 全特化版本" << endl;
}

int main() {
    // 使用泛化版本
    func(3, 5.6);

    // 使用 <int, int> 全特化版本
    func(5, 8);

    // 使用 <double, double> 全特化版本
    func(6.5, 3.5);

    return 0;
}