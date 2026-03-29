/**
 * 类型转换构造函数、类型转换运算符，类成员指针
 *
 * (c) 类对象转化为函数指针
 */

#include <functional>
#include <iostream>

using namespace std;

class MyInt {
public:
    // 定义函数指针类型，代表函数只有一个int形参，没有返回值类型
    // typedef void (*tfpoint)(int);
    using tfpoint = void (*)(int);

    // 静态成员函数
    static void func(int i) {
        cout << "func(int)" << endl;
    }

    MyInt(int i = 0) : m_num(i) {
    }

    ~MyInt() {
    }

    // 类型转换运算符，将本类的类型对象转换为一个函数指针类型
    operator tfpoint() {
        return func;
    }

private:
    int m_num;
};

int main() {
    MyInt i(10);

    // 这里会隐式调用类型转换运算符，将本类的类型对象转换为一个函数指针类型，最后调用静态成员函数 func()
    i(3);

    // 显式调用类型转换运算符，将本类的类型对象转换为一个函数指针类型，最后调用静态成员函数 func()
    i.operator MyInt::tfpoint()(5);

    return 0;
}