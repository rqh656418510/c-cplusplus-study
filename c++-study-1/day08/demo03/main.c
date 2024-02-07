/*
 * 1. 函数类型做函数参数
*/

#include <stdio.h>

// 定义函数类型
typedef int (MyFuncType)(int a, int b);

int add(int a, int b) {
	return a + b;
}

int mult(int a, int b) {
	return a * b;
}

// 函数类型作为函数参数
int callbackFunc(MyFuncType func) {
	return func(3, 6);
}

int main() {
	// 通过函数类型定义函数指针类型
	MyFuncType* myFuncType = NULL;

	myFuncType = add;
	int result = callbackFunc(*myFuncType);
	printf("result = %d\n", result);

	myFuncType = mult;
	int result2 = callbackFunc(*myFuncType);
	printf("result = %d\n", result2);

	return 0;
}