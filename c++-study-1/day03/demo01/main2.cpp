/**
 * 1. 构造函数的分类
 */

#include <iostream>

using namespace std;

class Test {

private:
    int _a;
    int _b;

public:

    // 无参数的构造函数
    Test() {
        _a = 1;
        _b = 2;
    }

    // 带参数的构造函数
    Test(int a, int b) {
        _a = a;
        _b = b;
    }

    // 赋值构造函数
    Test(const Test &obj) {
        _a = obj._a;
        _b = obj._b;
    }

};