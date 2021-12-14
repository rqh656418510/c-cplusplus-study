/*
 * 1. ���������뺯��ָ�����͵�Ӧ��
*/

#include <stdio.h>

int add(int a, int b) {
	return a + b;
}

int main() {

	// 1. ���庯������
	typedef int (MyFuncType)(int a, int b);

	// ͨ���������Ͷ��庯��ָ������
	MyFuncType* myFuncType = add;
	int result = myFuncType(1, 3);
	printf("%d + %d = %d\n", 1, 3, result);

	// 2. ����һ������ָ�����ͣ���������ڴ�ռ䣩
	typedef int (*MyFuncPointType)(int a, int b);

	// �Ӳ�����"&"���Ŷ��ǿ��Եģ����������"&"���ţ����Խ��C���԰汾�ļ�������
	// MyFuncPointType myFuncPointType = &add;

	MyFuncPointType myFuncPointType = add;
	int result2 = myFuncPointType(4, 5);
	printf("%d + %d = %d\n", 4, 5, result2);

	// 3. ���庯��ָ�������������ڴ�ռ䣩
	int (*MyFuncPointVar)(int a, int b);
	MyFuncPointVar = add;
	int result3 = MyFuncPointVar(7, 9);
	printf("%d + %d = %d\n", 7, 9, result3);

	return 0;
}