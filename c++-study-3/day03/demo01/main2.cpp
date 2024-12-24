/**
 * 理解函数模板
 */

#include <iostream>

using namespace std;

// 函数模板
// 使用模板的非类型参数（必须是整数类型，整数或者地址/引用都可以），非类型参数都是常量，只能使用，不能修改
template<typename T, int SIZE>
void sort(T *array) {
    // 冒泡排序
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

int main() {
    int array[] = {12, 4, 15, 3, 9, 23, 63};
    const int size = sizeof(array) / sizeof(array[0]);

    sort<int, size>(array);

    for (int item: array) {
        cout << item << " ";
    }
    cout << endl;

    return 0;
}