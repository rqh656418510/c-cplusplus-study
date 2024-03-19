/**
 * explicit 关键字的作用
 *
 * <p> explicit 关键字用于声明类的有参构造函数为显式构造函数，防止其被隐式调用（即防止构造调用时进行隐式类型转换）
 * <p> 这样可以避免一些意外的类型转换和编译器自动调用构造函数的情况
 */

#include <iostream>

using namespace std;

class MyString {

public:
    MyString(char *str) {
        m_str = str;
    }

    explicit MyString(int size) {
        m_size = size;
    }

private:
    char *m_str;
    int m_size;
};

int main() {
    MyString str("abc");
    MyString str2 = "abc";

    MyString str3(10);
    // MyString str4 = 10;     // 默认情况下，这里会发生隐式类型转换，使用 explicit 关键字修饰函数后，可以禁止隐式类型转换

    return 0;
}
