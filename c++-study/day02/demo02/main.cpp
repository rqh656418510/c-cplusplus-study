/**
 * 1. C++�е�����֮�����ã�ʹ�ñ�����ʼ�� const ���ã�
 */

#include <iostream>

using namespace std;

int main() {
    int a = 10;
    const int &b = a;
    // b = 11;  �Ǵ���д�������ﲻ��ͨ�����øı�a��ֵ���޷�ͨ������

    // ֻ����ָ�����ı����õ�ֵ
    int * p = (int*) &b;
    *p = 11;

    printf("a:%d\n", a);
    printf("b:%d\n", b);
    printf("&a:%d\n", &a);
    printf("&b:%d\n", &b);
    return 0;
}

