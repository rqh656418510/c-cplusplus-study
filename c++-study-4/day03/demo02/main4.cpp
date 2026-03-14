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

public:
    int val1;
    int val2;
};

void test01() {
    std::cout << "======== test01() =======" << std::endl;

    MyValue mv;
    std::cout << "--------------" << std::endl;

    // 会发生构造函数隐式类型转换，先调用有参构造函数，然后再调用赋值运算符重载函数
    // 这里的类型转换会产生临时对象、隐式类型转换以保证代码可以正常运行
    mv = 2000;

    std::cout << "--------------" << std::endl;
}

void test02() {
    std::cout << "======== test02() =======" << std::endl;

    // 将定义对象和给对象初始化值写在同一行，这种写法不会产生临时对象，性能更高
    // 为 mv 对象预留内存空间，用 1000 构造 mv 对象，而且是直接构造在 mv 对象预留的内存空间中
    MyValue mv = 1000;
}

int main() {
    test01();
    test02();
    return 0;
}