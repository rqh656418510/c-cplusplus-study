/**
 * 程序转化语义
 */

#include <iostream>

class X {

public:
    // 构造函数
    X() {
        std::cout << "X()" << std::endl;
    }

    // 拷贝构造函数
    X(const X& x) {
        m_i = 0;
        std::cout << "X(const X& x)" << std::endl;
    }

    // 析构函数
    ~X() {
        std::cout << "~X()" << std::endl;
    }

public:
    int m_i;
};

// 参数的初始化
void func(X x) {
    std::cout << "func(X x)" << std::endl;
}

// 返回值的初始化
X func2() {
    X x0;
    return x0;
}

void test01() {
    X x0;
    x0.m_i = 15;

    X x1 = x0;  // 第一步：定义一个对象，为对象分配内存；第二步：直接调用对象的拷贝构造函数，即 x1.X::X(x0)，完成对象的初始化

    X x2(x0);

    X x3 = (x0);
}

void test02() {
    X x0;
    func(x0);  // 调用拷贝构造函数，创建了一个临时对象 x0 的副本，并将其作为参数传递给 func 函数
}

void test03() {
    X x = func2();  // 调用拷贝构造函数，创建了一个临时对象 x0 的副本，并将其作为返回值传递给 x  
}

int main() {
    // test01();
    // test02();
    test03();
    return 0;
}