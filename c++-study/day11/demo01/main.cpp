/*
 * 1. ��ͨ��ָ��Ҳ��һ�ֵ�����
*/

#include <iostream>

using namespace std;

int main() {
    int array[5] = {1, 2, 3, 4, 5};
    int length = sizeof(array) / sizeof(int);
    int *p = array;

    for (int i = 0; i < length; i++) {
        cout << *(p++) << " ";
    }
    return 0;
}