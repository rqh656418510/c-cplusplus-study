/**
 * 1. C++ 中的对数组建立引用
 */

#include <iostream>

using namespace std;

// 对数组建立引用（第一种方式）
void test01() {
    int arr[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }

    // 给数组起别名
    int (&pArr)[10] = arr;

    for (int j = 0; j < 10; j++) {
        cout << pArr[j] << " ";
    }
    cout << endl;
}

// 对数组建立引用（第二种方式）
void test02() {
    int arr[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }

    // 定义一个具有 10 个元素的 int 类型的数组
    typedef int(ARRAYREF)[10];

    // 给数组起别名
    ARRAYREF &pArr = arr;

    for (int j = 0; j < 10; j++) {
        cout << pArr[j] << " ";
    }
    cout << endl;
}

int main() {
    test01();
    test02();
    return 0;
}
