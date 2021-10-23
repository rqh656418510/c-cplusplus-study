/**
 * 1. 构造函数的调用
 */

#include <iostream>

using namespace std;

class Test {

private:
    int _a;
    int _b;

public:

    Test() {
        _a = 1;
        _b = 1;
    }

    Test(int a) {
        _a = a;
        _b = 3;
    }

    Test(int a, int b) {
        _a = a;
        _b = b;
    }


public:

    int getA() const {
        return _a;
    }

    int getB() const {
        return _b;
    }
};

int main() {
    // C++编译器调用无参构造函数
    Test t0;
    printf("a = %d, b = %d\n", t0.getA(), t0.getB());

    // C++编译器调用有参构造函数(等号法)
    Test t1 = (1, 2, 3, 4, 5);
    printf("a = %d, b = %d\n", t1.getA(), t1.getB());

    // C++编译器调用有参构造函数(括号法)
    Test t2(10, 20);
    printf("a = %d, b = %d\n", t2.getA(), t2.getB());

    // 手动调用构造函数生成一个对象(直接调用构造函数法)
    Test t3 = Test(100, 200);
    printf("a = %d, b = %d\n", t3.getA(), t3.getB());

    return 0;
}
