/**
 * 1. C++中的const关键字
 */

#include <iostream>

using namespace std;

int main() {
    const int a = 7;
    int *p = (int *) &a;
    *p = 8;
    cout << a << " "<< *p;  // 输出结果为：7 8
    return 0;
}
