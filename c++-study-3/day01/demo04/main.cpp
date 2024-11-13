/**
 * const、指针、引用的结合使用
 */

#include <iostream>

using namespace std;

int main() {
    // 常量引用
    // const int &a = 30;

    // 在内存的0x0018ff44位置写一个4字节的10
    // int *p = (int *) 0x0018ff44;

    // 二级指针
    int a = 10;
    int *p = &a;
    int **q = &p;
    cout << **q << endl;

    return 0;
}
