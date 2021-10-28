/**
 * 1. 使用构造函数的初始化列表，初始化 const 成员和引用成员
 */

#include <iostream>

using namespace std;

class A {
private:
    int i;
    int &j;
    const int c;

public:

    A(int x) {
        i = -1;
        c = 5;    // C++编译不通过，必须通过初始化列表来初始化
        j = x;    // C++编译不通过，必须通过初始化列表来初始化
    }
};

int main() {
    A a(3);
    return 0;
}