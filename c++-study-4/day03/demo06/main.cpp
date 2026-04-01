/**
 * 类成员指针
 *
 * (e) 类成员指针
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
    return 0;
}