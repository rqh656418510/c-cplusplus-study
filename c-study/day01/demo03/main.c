/**
 * 1. C����Ƕ�׻�����
 */

#include <stdio.h>

int main() {
    int a;
    int b;
    int c;

    __asm
    {
        mov a, 3        // 3��ֵ����a��Ӧ�ڴ��λ��
        mov b, 4        // 4��ֵ����a��Ӧ�ڴ��λ��
        mov eax, a      // ��a�ڴ��ֵ����eax�Ĵ���
        add eax, b      // eax��b��ӣ��������eax
        mov c, eax      // eax��ֵ����c��
    }

    printf("c = %d\n", c);
    return 0;
}