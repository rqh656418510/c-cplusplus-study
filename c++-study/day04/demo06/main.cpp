/**
 * 1. 使用成员函数和友元函数实现一元操作符的重载
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
	// 使用类成员函数完成 "前置--" 操作符的重载
	Complex& operator--() {
		this->a--;
		this->b--;
		return *this;
	}

	// 使用类成员函数完成 "后置--" 操作符的重载
	// 使用占位参数进行函数重载，是为了解决与 "前置--" 类成员函数冲突的问题
	Complex operator--(int) {
		Complex tmp(this->a, this->b);
		this->a--;
		this->b--;
		return tmp;
	}

	// 声明用于 "前置++" 操作符重载的友元函数
	friend Complex& operator++(Complex& c1);

	// 声明用于 "后置++" 操作符重载的友元函数
	// 使用占位参数进行函数重载，是为了解决与 "前置++" 友元函数冲突的问题
	friend Complex operator++(Complex& c1, int);
};

// 定义友元函数完成 "前置++" 操作符的重载
Complex& operator++(Complex& c1)
{
	c1.a++;
	c1.b++;
	return c1;
}

// 定义友元函数完成 "后置++" 操作符的重载
Complex operator++(Complex& c1, int) {
	Complex tmp(c1.a, c1.b);
	c1.a++;
	c1.b++;
	return tmp;
}

int main() {
	Complex c1(1, 2), c2(8, 9), c3(15, 16), c4(24, 25);

	// 使用友元函数完成 "前置++" 操作符的重载
	++c1;
	c1.print();

	// 使用类成员函数完成 "前置--" 操作符的重载
	--c2;
	c2.print();

	// 使用友元函数完成 "后置++" 操作符的重载
	Complex c5 = c3++;
	c3.print();
	c5.print();

	// 使用类成员函数完成 "后置--" 操作符的重载
	Complex c6 = c4--;
	c4.print();
	c6.print();

	return 0;
}

