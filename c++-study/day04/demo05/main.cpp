/**
 * 1. 使用成员函数和友元函数实现二元操作符的重载
 * 2. 除了使用友元函数外，还可以使用全局函数（普通函数）来实现操作符的重载，不同的是使用友元函数更方便，可以直接访问类的所有私有（private）成员和保护（protected）成员
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

	void print() {
		cout << "a=" << this->a << ", b=" << this->b << endl;
	}

public:
	// 使用类成员函数完成 "-" 操作符的重载
	Complex operator-(Complex& c2) {
		Complex c3(this->a - c2.a, this->b - c2.b);
		return c3;
	}

	// 声明用于 "+" 操作符重载的友元函数
	friend Complex operator+(Complex& c1, Complex& c2);
};

// 定义友元函数完成 "+" 操作符的重载
Complex operator+(Complex& c1, Complex& c2) {
	Complex c3(c1.a + c2.a, c1.b + c2.b);
	return c3;
}

int main() {
	Complex c1(1, 2), c2(3, 4);

	// 直接调用友元函数
	Complex c3 = operator+(c1, c2);
	c3.print();

	// 使用友元函数完成 "+" 操作符的重载
	Complex c4 = c1 + c2;
	c4.print();

	// 直接调用类成员函数
	Complex c5 = c1.operator-(c2);
	c5.print();

	// 使用类成员函数完成 "-" 操作符的重载
	Complex c6 = c1 - c2;
	c6.print();

	return 0;
}