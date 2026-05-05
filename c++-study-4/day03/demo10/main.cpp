/**
 * 成员函数模板，显式实例化、声明
 *
 * (a) 普通类的成员函数模板
 */

#include <iostream>

using namespace std;

// 普通类
class Test {
public:
    // 成员函数模板
    template <typename T>
    T sum(T v1, T v2) {
        return v1 + v2;
    }
};

int main() {
    Test obj;

    // 函数模板支持自动推断模板参数类型
    int result = obj.sum(3, 5);

    cout << result << endl;

    return 0;
}