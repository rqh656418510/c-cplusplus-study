/**
 * 1. C++�еĺ��������뺯��Ĭ�ϲ���
 */

#include <iostream>

using namespace std;

int func(int a, int b, int c = 0) {
    return a * b * c;
}

int func(int a, int b) {
    return a + b;
}

int func(int a) {
    return a;
}

int main() {
    int c = 0;
    // c = func(1, 2); // ���ڶ����ԣ�����ʧ�ܣ����벻��ͨ��
    printf("c = %d\n", c);
    return 0;
}