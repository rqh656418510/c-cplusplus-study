/**
 * 深入理解C++的new和delete
 */

#include <iostream>

using namespace std;

void test01() {
    int *p = (int *) malloc(sizeof(int));
    if (p == nullptr) {
        return;
    }

    *p = 20;
    cout << "p = " << *p << endl;

    free(p);
}

void test02() {
    int *p = new int(20);
    cout << "p = " << *p << endl;
    delete p;

    int *arr = new int[5](); // 数组初始化为 0
    for (int i = 0; i < 5; ++i) {
        cout << arr[i] << " ";
    }
    delete[] arr;
}

/**
 * new 的几种用法
 */
void test03() {
    // 第一种用法
    int *p1 = new int(20);
    delete p1;

    // 第二种用法
    int *p2 = new(nothrow) int; // 即使内存分配失败，也不抛出异常
    delete p2;

    // 第三种用法
    const int *p3 = new const int(30);
    delete p3;

    // 第四种用法
    int data = 0;
    int *p4 = new(&data) int(50);
    cout << "data = " << data << endl; // 输出 50
}

int main() {
    // test01();
    // test02();
    test03();
    return 0;
}
