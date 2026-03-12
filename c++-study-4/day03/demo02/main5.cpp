/**
 * 临时对象深入探讨、解析，提高性能手段
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

    // 赋值运算符重载函数
    MyValue& operator=(const MyValue& mv) {
        std::cout << "MyValue& operator=(const MyValue&)" << std::endl;
        val1 = mv.val1;
        val2 = mv.val2;
        return *this;
    }

    // 析构函数
    ~MyValue() {
        std::cout << "~MyValue()" << std::endl;
    }

    // 成员函数（当函数的返回值是临时对象时，编译器可能会调用拷贝构造函数生成一个临时对象，并将该临时对象作为函数返回值）
    MyValue Double1(MyValue& mv) {
        MyValue tmp;
        tmp.val1 = mv.val1 * 2;
        tmp.val2 = mv.val2 * 2;
        return tmp;
    }

    // 优化后的写法，为了避免编译器可能调用拷贝构造函数生成一个临时对象
    MyValue Double2(MyValue& mv) {
        return MyValue(mv.val1 * 2, mv.val2 * 2);
    }

public:
    int val1;
    int val2;
};

int main() {
    MyValue mv(10, 20);

    std::cout << "------------" << std::endl;

    // 不接管临时对象，临时对象会立即析构
    mv.Double1(mv);

    // 其他常见写法（接管临时对象，临时对象不会立即析构）
    // MyValue mv2 = mv.Double1(mv);
    // MyValue&& refVal = mv.Double1(mv);  // 临时对象是右值，所以可以被右值引用绑定

    std::cout << "------------" << std::endl;

    return 0;
}