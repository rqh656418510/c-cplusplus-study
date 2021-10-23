/**
 * 1. 构造函数的分类及调用
 */

#include <iostream>

using namespace std;

class Test {

private:
    int _a;
    int _b;

public:

    // 无参数构造函数
    Test() {
        _a = 1;
        _b = 2;
        cout << "调用无参数构造函数" << endl;
    }

    // 带参数的构造函数
    Test(int a, int b) {
        _a = a;
        _b = b;
        cout << "调用带参数的构造函数" << endl;
    }

    // 赋值构造函数
    Test(const Test &obj) {
        _a = obj._a;
        _b = obj._b;
        cout << "调用赋值构造函数" << endl;
    }

    int getA() const {
        return _a;
    }

    int getB() const {
        return _b;
    }

};

int main() {
    Test t1;
    printf("a = %d, b = %d\n", t1.getA(), t1.getB());

    Test t2 = Test(10, 20);
    printf("a = %d, b = %d\n", t2.getA(), t2.getB());

    Test t3 = Test(t1);
    printf("a = %d, b = %d\n", t3.getA(), t3.getB());

    return 0;
}