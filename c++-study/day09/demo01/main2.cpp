/*
 * 1. 函数模板的当函数参数
*/

#include <iostream>

using namespace std;

// 使用函数模板，实现数组排序
template <typename T1>

void arraySort(T1* array, int size, bool asc = true) {
    if (array == NULL || size == 0) {
        return;
    }

    T1 tmp;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            // 升序排序（从小到大）
            if (asc) {
                if (array[i] > array[j]) {
                    tmp = array[i];
                    array[i] = array[j];
                    array[j] = tmp;
                }
            }
            // 降序排序（从大到小）
            else {
                if (array[i] < array[j]) {
                    tmp = array[i];
                    array[i] = array[j];
                    array[j] = tmp;
                }
            }
        }
    }
}

// 使用函数模板，打印数组
template <typename T2>

void printArray(T2* array, int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main() {
    int array[] = { 32, 16, 29, 9, 43, 53, 23 };
    int size = sizeof(array) / sizeof(*array);

    cout << "排序之前: ";
    printArray<int>(array, size);

    arraySort<int>(array, size, false);

    cout << "排序之后: ";
    printArray<int>(array, size);

    cout << "------------------------------" << endl;

    char array2[] = { 'c', 'z', 'h', 'i', 'q', 'm' };
    int size2 = sizeof(array2) / sizeof(*array2);

    cout << "排序之前: ";
    printArray<char>(array2, size2);

    arraySort<char>(array2, size2);

    cout << "排序之后: ";
    printArray<char>(array2, size2);

    return 0;
}