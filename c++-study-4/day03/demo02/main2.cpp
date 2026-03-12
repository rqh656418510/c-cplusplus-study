/**
 * 临时对象深入探讨、解析，提高性能手段
 */

#include <iostream>

class MyValue {
public:
    // 有参构造函数
    MyValue(int v1 = 0, int v2 = 0) : val1(v1), val2(v2) {
        std::cout << "CTempValue()" << std::endl;
    }

    // 拷贝构造函数
    MyValue(const MyValue& mv) : val1(mv.val1), val2(mv.val2) {
        std::cout << "CTempValue(const CTempValue&)" << std::endl;
    }

    // 析构函数
    ~MyValue() {
        std::cout << "~CTempValue()" << std::endl;
    }

    // 成员函数（以传值的方式给函数传递参数，会产生临时对象）
    int sum1(MyValue mv) {
        int tmp = mv.val1 + mv.val2;
        mv.val1 = 1000;
        return tmp;
    }

    // 成员函数（以传引用的方式给函数传递参数，不会产生临时对象）
    int sum2(MyValue& mv) {
        int tmp = mv.val1 + mv.val2;
        mv.val1 = 1000;
        return tmp;
    }

public:
    int val1;
    int val2;
};

void test01() {
    std::cout << "======== test01() =======" << std::endl;

    MyValue mv(10, 20);     // 会调用有参构造函数
    int sum = mv.sum1(mv);  // 会调用拷贝构造函数（性能差）

    std::cout << "sum = " << sum << std::endl;
    std::cout << "mv.val1 = " << mv.val1 << std::endl;
}

void test02() {
    std::cout << "======== test02() =======" << std::endl;

    MyValue mv(30, 40);     // 会调用有参构造函数
    int sum = mv.sum2(mv);  // 不会调用拷贝构造函数（性能高）

    std::cout << "sum = " << sum << std::endl;
    std::cout << "mv.val1 = " << mv.val1 << std::endl;
}

int main() {
    test01();
    test02();
    return 0;
}