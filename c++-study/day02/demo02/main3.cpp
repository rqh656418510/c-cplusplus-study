/**
 * 1. C++�е�����֮�����ã�ʹ��������������ʼ�� const ���ã�
 */

#include <iostream>

using namespace std;

int main() {
    const int b = 10;
    printf("b:%d\n", &b);

    // int &a = 19; ������const�ؼ��֣������ʧ��

    const int &a = 19;
    printf("&a:%d \n", &a);
    return 0;
}