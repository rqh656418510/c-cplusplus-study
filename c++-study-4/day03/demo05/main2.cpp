/**
 * 类型转换构造函数、类型转换运算符
 *
 * (a) 类型转换构造运算符
 */

#include <iostream>

using namespace std;

class MyInt {
public:
    // 有参构造函数，同时也称为类型转换构造函数
    MyInt(int i = 0) : m_num(i) {
    }

    ~MyInt() {
    }

    // 类型转换运算符，将类类型转换为其他类型
    operator int() const {
        cout << "operator int() const" << endl;
        return m_num;
    }

private:
    int m_num;
};

int main() {
    MyInt i(30);

    // 将类类型转换为其他类型（隐式调用类型转换运算符）
    int i2 = i + 10;
    cout << i2 << endl;

    // 将类类型转换为其他类型（显式调用类型转换运算符）
    int i3 = i.operator int() + 15;
    cout << i3 << endl;

    // 将类类型转换为其他类型（显式调用类型转换运算符）
    int i4 = static_cast<int>(i) + 25;
    cout << i4 << endl;

    return 0;
}