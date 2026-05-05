/**
 * 类型转换构造函数、类型转换运算符
 *
 * (a) 类型转换构造函数
 */

#include <iostream>

using namespace std;

class MyInt {
public:
    // 有参构造函数，同时也称为类型转换构造函数
    MyInt(int i = 0) : m_num(i) {
        cout << "MyInt(int)" << endl;
    }

    ~MyInt() {
        cout << "~MyInt()" << endl;
    }

    int getNumber() {
        return m_num;
    }

private:
    int m_num;
};

int main() {
    // 这里会发生隐式类型转换，调用的是类型转换构造函数
    // 编译器用 10 这个数字通过调用 MyInt 类的构造函数创建一个临时 MyInt 对象，并将这个临时对象构造到 i 这个预留空间里面去
    MyInt i = 10;
    cout << i.getNumber() << endl;

    // 等效于上面的写法，会发生隐式类型转换，调用的是类型转换构造函数
    // MyInt i = MyInt(10);

    // 这里不会发生隐式类型转换，调用的是有参构造函数（即类型转换构造函数）
    MyInt i2(30);
    cout << i2.getNumber() << endl;

    return 0;
}