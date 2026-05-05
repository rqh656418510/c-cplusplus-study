/**
 * 临时对象深入探讨、解析，提高性能手段
 *
 * (f) 类外实现运算符重载时，函数将临时对象作为返回值，会产生临时对象
 */

#include <iostream>

class MyValue {
public:
    // 有参构造函数
    MyValue(int v1 = 0, int v2 = 0) : val1(v1), val2(v2) {
        std::cout << "MyValue()" << std::endl;
    }

    // 拷贝构造函数
    MyValue(const MyValue& mv) : val1(mv.val1), val2(mv.val2) {
        std::cout << "MyValue(const MyValue&)" << std::endl;
    }

    // 析构函数
    ~MyValue() {
        std::cout << "~MyValue()" << std::endl;
    }

public:
    int val1;
    int val2;
};

// 类外实现运算符重载（当函数的返回值是临时对象时，编译器可能会调用拷贝构造函数生成一个临时对象，并将该临时对象作为函数返回值）
MyValue operator+(MyValue& m1, MyValue& m2) {
    std::cout << "operator+()" << std::endl;
    MyValue result;
    result.val1 = m1.val1 + m2.val1;
    result.val2 = m1.val2 + m2.val2;
    return result;
}

// 优化后的写法，为了避免编译器可能调用拷贝构造函数生成一个临时对象
MyValue operator-(MyValue& m1, MyValue& m2) {
    std::cout << "operator-()" << std::endl;
    return MyValue(m1.val1 - m2.val1, m1.val2 - m2.val2);
}

int main() {
    MyValue mv1(10, 20);
    MyValue mv2(30, 40);

    std::cout << "------------" << std::endl;

    // 不接管临时对象，临时对象会立即析构
    mv1 + mv2;

    // 其他常见写法（接管临时对象，临时对象不会立即析构）
    // MyValue mv3 = mv1 + mv2;
    // MyValue&& refVal = mv1 + mv2;  // 临时对象是右值，所以可以被右值引用绑定

    std::cout << "------------" << std::endl;

    return 0;
}