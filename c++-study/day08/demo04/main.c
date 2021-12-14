/*
 * 1. 函数指针做函数参数
 * a) 将 “函数的调用” 和 “函数的实现” 解耦
 * b) 可以模拟 C++ 的多态机制（提前布局 VPTR 指针和虚函数表，找虚函数入口地址来实现函数调用）
*/

#include <stdio.h>

int add(int a, int b) {
	return a + b;
}

int mult(int a, int b) {
	return a * b;
}

// 函数指针做函数参数
int callbackFunc(int (*MyFunc)(int a, int b)) {
	return MyFunc(3, 4);
}

int main() {
	// 定义函数指针变量
	int (*myFuncVar)(int a, int b);

	myFuncVar = add;
	int result = callbackFunc(myFuncVar);
	printf("result = %d\n", result);

	myFuncVar = mult;
	int result2 = callbackFunc(myFuncVar);
	printf("result = %d\n", result2);

	return 0;
}