/**
 * 1. C++ 对 C 语言的增强
 */

#include <iostream>

using namespace std;

int a;

int main() {

    /************************ 双冒号作用域限定运算符 ******************************/

    float a;
    a = 3.14;
    ::a = 6;
    cout << "local variable a = " << a << endl;
    cout << "global variable a = " << ::a << endl;
    return 0;
}
