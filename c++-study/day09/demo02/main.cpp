/*
 * 1. 函数模板与普通函数
*/

#include <iostream>

using namespace std;

template <typename T>

void myswap(T& a, T& b) {
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
	cout << "模板函数被调用" << endl;
}

void myswap(int a, char b) {
	cout << "a = " << a << ", b = " << b << endl;
	cout << "普通函数被调用" << endl;
}

int main() {
	int a = 10;
	char c = 'z';
	myswap(a, c); // 调用普通函数
	myswap(c, a); // 调用普通函数，会进行隐式的类型转换
	myswap(a, a); // 调用函数模板（本质是类型参数化），将严格地按照类型进行匹配，不会自动进行类型转换
	return 0;
}