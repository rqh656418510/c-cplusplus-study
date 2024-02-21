/**
 * 1. C++ 中引用的本质
 */

#include <iostream>

using namespace std;

// C++ 编译器发现函数参数是引用时，会自动转换为 int * const ref = &a
void testFunc(int &ref) {
    ref = 100;
}

int main() {
    int a = 10;
    int &aRef = a;      // C++ 编译器会自动转换为 int * const aRef = &a，这就能说明引用为什么必须初始化
    aRef = 20;          // C++ 编译器发现 aRef 是引用时，会自动转换为 *aRef = 20
    testFunc(a);
    cout << "a = " << a << endl;
    cout << "aRef = " << aRef << endl;
}