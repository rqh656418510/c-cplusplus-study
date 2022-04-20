/*
 * 1. 类模板的使用
 * a) 所有的类模板函数写在类的外部（在不同的 .h 和 .cpp 中）
*/

#include "complex.hpp"  // 这里引入的是 `.hpp` 文件，而不是 `.h` 头文件，否则 C++ 编译器会编译失败

int main() {
	Complex<int> c1(6, 13);
	Complex<int> c2(23, 34);
	c1.print();
	c2.print();

	Complex<int> c3 = c1 + c2;
	cout << c3 << endl;

	return 0;
}