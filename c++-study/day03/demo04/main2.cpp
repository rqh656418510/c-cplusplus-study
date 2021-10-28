/**
 * 1. 构造函数的初始化列表
 */

#include <iostream>

using namespace std;

class A {

private:
    int i;
    int &j;
    const int c;

public:

    // 构造函数初始化列表
    A(int x, int y) : c(x), j(y) {
        i = -1;
    }

};

int main() {
    int m;
    A a(5, m);  // C++编译可以通过
    return 0;
}