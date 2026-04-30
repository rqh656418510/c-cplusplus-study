/**
 * 类型转换构造函数、类型转换运算符
 *
 * (d) 类型转换的二义性问题
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

    // 类型转换运算符，将类类型转换为其他类型
    operator double() const {
        cout << "operator int() const" << endl;
        return m_num;
    }

private:
    int m_num;
};

int main() {
    MyInt i(30);

    // 编译出错，存在二义性，编译器不知道调用 operator int() 还是 operator double() 运算符
    // int i2 = i + 10;

    return 0;
}