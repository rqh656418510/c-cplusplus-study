/*
 * 模板全特化、偏特化(局部特化)
 *
 * (a) 类模板全特化 - 常规全特化
 */

#include <iostream>

using namespace std;

// 定义类模板（泛化版本）
template <typename T, typename U>
class TestClass {
public:
    TestClass() {
        cout << "TestClass() 泛化版本" << endl;
    }

    void print(T t, U u) {
        cout << "printf() 泛化版本" << endl;
    }
};

// 当 T 和 U 这两个模板参数都为 int 类型时，实现一个类模板的全特化版本
template <>
class TestClass<int, int> {
public:
    TestClass() {
        cout << "TestClass() 特化版本" << endl;
    }

    void print(int t, int u) {
        cout << "printf(int, int) 特化版本" << endl;
    }
};

// 当 T 和 U 这两个模板参数都为 double 类型时，实现一个类模板的全特化版本
template <>
class TestClass<double, double> {
public:
    TestClass() {
        cout << "TestClass() 特化版本" << endl;
    }

    void print(double t, double u) {
        cout << "printf(double, double) 特化版本" << endl;
    }
};

int main() {
    // 使用泛化版本
    TestClass<int, double> t;
    t.print(3, 5.61);

    // 使用 <int, int> 特化版本
    TestClass<int, int> t2;
    t2.print(7, 9);

    // 使用 <double, double> 特化版本
    TestClass<double, double> t3;
    t3.print(2.45, 6.7);

    return 0;
}