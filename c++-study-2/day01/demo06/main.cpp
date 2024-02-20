/**
 * 1. C++ 中的引用
 */

#include <iostream>

using namespace std;

// 引用的语法：Type & 别名 = 原名
void test01() {
    int a = 100;
    int &b = a;
    b = 200;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

// 引用必须初始化
void test02() {
    // int &a;  必须初始化，否则编译不通过
    int b = 10;
    int c = 20;
    int &d = b;
    // int &d = c;  引用初始化后不可修改，否则编译不通过

}

int main() {
    test01();
    test02();
    return 0;
}
