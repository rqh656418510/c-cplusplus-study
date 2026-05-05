/*
 * 模板全特化、偏特化(局部特化)
 *
 * (f) 函数模板 "偏特化"
 */

#include <iostream>

using namespace std;

// 定义函数模板（泛化版本）
template <typename T, typename U>
void func(T t, U u) {
    cout << "func(T, U) 泛化版本" << endl;
}

// 错误写法，编译不通过，因为函数模板不支持偏特化
/*
template <typename U>
void func<int, U>(int i, U u) {
    cout << "func(int, U) 偏特化版本" << endl;
}
*/

int main() {
    return 0;
}