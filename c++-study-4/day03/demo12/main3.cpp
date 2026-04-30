/*
 * 模板全特化、偏特化(局部特化)
 *
 * (c) 类模板偏特化 - 从类模板的参数数量上进行偏特化
 */

#include <iostream>

using namespace std;

// 定义类模板（泛化版本）
template <typename T, typename U, typename W>
class TestClass {
public:
    TestClass() {
        cout << "TestClass() 泛化版本" << endl;
    }

    void print(T t, U u, W w) {
        cout << "printf(T, U, W) 泛化版本" << endl;
    }
};

// 类模板偏特化，从参数数量上进行偏特化（有两个模板参数绑定了具体类型，剩下一个模板参数没绑定具体类型）
template <typename U>
class TestClass<int, U, int> {
public:
    TestClass() {
        cout << "TestClass() 偏特化版本" << endl;
    }

    void print(int t, U u, int) {
        cout << "printf(int, U, int) 偏特化版本" << endl;
    }
};

// 类模板偏特化，从参数数量上进行偏特化（有两个模板参数绑定了具体类型，剩下一个模板参数没绑定具体类型）
template <typename U>
class TestClass<double, U, double> {
public:
    TestClass() {
        cout << "TestClass() 偏特化版本" << endl;
    }

    void print(double t, U u, double) {
        cout << "printf(double, U, double) 偏特化版本" << endl;
    }
};

int main() {
    // 使用泛化版本
    TestClass<int, int, double> t1;  // 这是泛化对象
    t1.print(1, 2, 3.14);

    // 使用 <int, U, int> 偏特化版本
    TestClass<int, double, int> t2;  // 这是偏特化对象
    t2.print(1, 2.55, 3);

    // 使用 <double, U, double> 偏特化版本
    TestClass<double, int, double> t3;  // 这是偏特化对象
    t3.print(1.0, 2, 3.14);

    return 0;
}