/*
 * 1. ������������������
*/

#include <stdio.h>

// ���庯������
typedef int (MyFuncType)(int a, int b);

int add(int a, int b) {
	return a + b;
}

int mult(int a, int b) {
	return a * b;
}

// ����������Ϊ��������
int callbackFunc(MyFuncType func) {
	return func(3, 6);
}

int main() {
	// ͨ���������Ͷ��庯��ָ������
	MyFuncType* myFuncType = NULL;

	myFuncType = add;
	int result = callbackFunc(*myFuncType);
	printf("result = %d\n", result);

	myFuncType = mult;
	int result2 = callbackFunc(*myFuncType);
	printf("result = %d\n", result2);

	return 0;
}