/*
 * 1. 函数模板的使用
*/

#include <iostream>

using namespace std;

// 模板声明
template <typename T>

// 函数定义
void myswap(T& a, T& b) {
	T temp;
	temp = a;
	a = b;
	b = temp;
}

int main() {

	// 自动数据类型推导
	int x = 1, y = 2;
	myswap(x, y);
	printf("x = %d, y = %d\n", x, y);

	// 自动数据类型推导
	double n = 0.5, m = 0.8;
	myswap(n, m);
	printf("n = %f, m = %f\n", n, m);

	// 显示类型调用（推荐）
	char i = 'h', j = 'e';
	myswap<char>(i, j);
	printf("n = %c, m = %c\n", i, j);

	return 0;
}