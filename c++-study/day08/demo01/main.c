/*
 * 1. ��������������ָ�����͵�Ӧ��
*/

#include <stdio.h>

int main() {
	// 1. �����������ͣ�������ڴ�ռ䣩
	typedef int(MyArray)[3];

	MyArray array;
	array[0] = 1;
	array[1] = 2;
	array[2] = 3;

	for (int i = 0; i < 3; i++) {
		printf("array[%d] = %d\n", i, array[i]);
	}

	printf("\n");

	// 2. ��������ָ�����ͣ���������ڴ�ռ䣩
	typedef int(*MyPointArray)[3];

	int a[3];
	MyPointArray pointArray;
	pointArray = &a;	// ������ָ������ָ��һ������
	(*pointArray)[0] = 11;
	(*pointArray)[1] = 22;
	(*pointArray)[2] = 33;

	for (int j = 0; j < 3; j++) {
		printf("a[%d] = %d, ", j, a[j]);
		printf("(*pointArray)[%d] = %d\n", j, (*pointArray)[j]);
	}

	printf("\n");

	// 3. ����һ������ָ���������������ڴ�ռ䣩
	int(*pointArrayVar)[3];

	int b[3];
	pointArrayVar = &b;		// ������ָ�����ָ��һ������
	(*pointArrayVar)[0] = 111;
	(*pointArrayVar)[1] = 222;
	(*pointArrayVar)[2] = 333;

	for (int n = 0; n < 3; n++) {
		printf("b[%d] = %d, ", n, b[n]);
		printf("(*pointArrayVar)[%d] = %d\n", n, (*pointArrayVar)[n]);
	}

}


