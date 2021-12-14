/*
 * 1. 函数类型与函数指针类型的应用
*/

#include <stdio.h>

int add(int a, int b) {
	return a + b;
}

int main() {

	// 1. 定义函数类型
	typedef int (MyFuncType)(int a, int b);

	// 通过函数类型定义函数指针类型
	MyFuncType* myFuncType = add;
	int result = myFuncType(1, 3);
	printf("%d + %d = %d\n", 1, 3, result);

	// 2. 定义一个函数指针类型（不会分配内存空间）
	typedef int (*MyFuncPointType)(int a, int b);

	// 加不加上"&"符号都是可以的，如果加上了"&"符号，可以解决C语言版本的兼容问题
	// MyFuncPointType myFuncPointType = &add;

	MyFuncPointType myFuncPointType = add;
	int result2 = myFuncPointType(4, 5);
	printf("%d + %d = %d\n", 4, 5, result2);

	// 3. 定义函数指针变量（会分配内存空间）
	int (*MyFuncPointVar)(int a, int b);
	MyFuncPointVar = add;
	int result3 = MyFuncPointVar(7, 9);
	printf("%d + %d = %d\n", 7, 9, result3);

	return 0;
}