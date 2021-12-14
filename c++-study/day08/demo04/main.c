/*
 * 1. ����ָ������������
 * a) �� �������ĵ��á� �� ��������ʵ�֡� ����
 * b) ����ģ�� C++ �Ķ�̬���ƣ���ǰ���� VPTR ָ����麯�������麯����ڵ�ַ��ʵ�ֺ������ã�
*/

#include <stdio.h>

int add(int a, int b) {
	return a + b;
}

int mult(int a, int b) {
	return a * b;
}

// ����ָ������������
int callbackFunc(int (*MyFunc)(int a, int b)) {
	return MyFunc(3, 4);
}

int main() {
	// ���庯��ָ�����
	int (*myFuncVar)(int a, int b);

	myFuncVar = add;
	int result = callbackFunc(myFuncVar);
	printf("result = %d\n", result);

	myFuncVar = mult;
	int result2 = callbackFunc(myFuncVar);
	printf("result = %d\n", result2);

	return 0;
}