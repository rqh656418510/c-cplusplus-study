/**
 * 成员函数模板，显式实例化、声明
 *
 * (c) 类模板的成员函数模板
 */

#include <iostream>

using namespace std;
template <typename A>
class Test {
public:
    // 成员函数模板
    template <typename B>
    void func(A v1, B v2);
};

// 类的声明与定义分开写
template <typename A>
template <typename B>
void Test<A>::func(A v1, B v2) {
    cout << v1 << ", " << v2 << endl;
}

int main() {
    // 类模板不支持自动推断模板参数类型
    Test<int> obj;

    // 函数模板支持自动推断模板参数类型
    obj.func(3, 5.3);

    return 0;
}