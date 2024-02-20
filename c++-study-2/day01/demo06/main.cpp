/**
 * 1. C++ 中的引用
 */

#include <iostream>

using namespace std;

// 引用的语法：Type & 别名 = 原名
void test01() {
    int a = 100;
    int &b = a;     // 建立引用
    b = 200;        // 变量赋值
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

int main() {
    test01();
    return 0;
}
