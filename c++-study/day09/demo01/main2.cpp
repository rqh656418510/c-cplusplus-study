/*
 * 1. ����ģ��ĵ���������
*/

#include <iostream>

using namespace std;

// ʹ�ú���ģ�壬ʵ����������
template <typename T1>

void arraySort(T1* array, int size, bool asc = true) {
    if (array == NULL || size == 0) {
        return;
    }

    T1 tmp;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            // �������򣨴�С����
            if (asc) {
                if (array[i] > array[j]) {
                    tmp = array[i];
                    array[i] = array[j];
                    array[j] = tmp;
                }
            }
            // �������򣨴Ӵ�С��
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

// ʹ�ú���ģ�壬��ӡ����
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

    cout << "����֮ǰ: ";
    printArray<int>(array, size);

    arraySort<int>(array, size, false);

    cout << "����֮��: ";
    printArray<int>(array, size);

    cout << "------------------------------" << endl;

    char array2[] = { 'c', 'z', 'h', 'i', 'q', 'm' };
    int size2 = sizeof(array2) / sizeof(*array2);

    cout << "����֮ǰ: ";
    printArray<char>(array2, size2);

    arraySort<char>(array2, size2);

    cout << "����֮��: ";
    printArray<char>(array2, size2);

    return 0;
}