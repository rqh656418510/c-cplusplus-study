/**
 * 1. 使用友元函数实现左移操作符的重载
 * 2. ”<<” 左移运算符和 “>>” 右移运算符的重载，只能使用友元函数或者全局函数，不能使用类成员函数，这也是友元函数的重要作用之一
 */

#include <iostream>

using namespace std;

class Complex {
private:
	int a;
	int b;

public:
	Complex(int a = 0, int b = 0) {
		this->a = a;
		this->b = b;
	}

public:
	// 声明友元函数实现 "<<" 左移操作符的重载
	friend ostream& operator<<(ostream& out, Complex& c1);
};

// 定义友元函数实现 "<<" 左移操作符的重载
ostream& operator<<(ostream& out, Complex& c1) {
	out << "a=" << c1.a << ", b=" << c1.b << endl;
	return out;
}

int main() {
	Complex c1(1, 2), c2(6, 9);
	cout << c1 << c2;
	return 0;
}