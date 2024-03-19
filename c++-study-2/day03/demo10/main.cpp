/**
 * explicit 关键字的作用
 *
 * <p> 在 C++ 中，`explicit` 关键字用于声明类的单参数构造函数为显式构造函数，防止其被隐式调用。
 * <p> 简而言之，`explicit` 关键字可以显式地禁止类构造函数的隐式转换，这样可以避免一些意外的类型转换和编译器自动调用构造函数的情况。
 */

#include <iostream>

using namespace std;

class MyClass {

public:
    explicit MyClass(int x) : num(x) {

    }

private:
    int num;

};

int main() {
    // MyClass obj = 42;   // 错误：不允许隐式转换
    MyClass obj2(42);   // 正确：显式转换
}
