/**
 * 1. C++�еĺ��������뺯��ָ��
 */

#include <iostream>
#include <string.h>

using namespace std;

int func(int x) {
    return x;
}

int func(int a, int b) {
    return a + b;
}

int func(const char *s) {
    return strlen(s);
}

// ��һ��д����������������
typedef int (FUNC)(int a);

// �ڶ���д������������ָ������
typedef int(*PFUNC)(int a, int b);

int main() {
    // ��������ĵ�һ��д�������庯��ָ�����͵ı���
    FUNC *FUNC = func;
    int c = FUNC(1);
    printf("c = %d\n", c);

    // ��������ĵڶ���д�������庯��ָ�����͵ı���
    PFUNC p = func;
    int d = p(3, 4);
    printf("d = %d\n", d);
    return 0;
}