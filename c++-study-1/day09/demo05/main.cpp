/*
 * 1. 类模板的使用
 * a) 所有的类模板函数写在类的内部
*/

#include <iostream>

using namespace std;

template <typename T>

class Complex {

public:

	// 构造函数
	Complex(T a, T b) {
		this->a = a;
		this->b = b;
	}

	// 类成员函数
	void print() {
		cout << "a = " << this->a << ", b = " << this->b << endl;
	}

	// 类成员函数，重载运算符 "+"
	Complex operator+(Complex& c2) {
		Complex tmp(this->a + c2.a, this->b + c2.b);
		return tmp;
	}

	// 友元函数，重载运算符 "<<"
	friend ostream& operator<<(ostream& out, Complex& c1) {
		cout << "a = " << c1.a << ", b = " << c1.b;
		return out;
	}

	// 友元函数
	friend Complex sub(Complex& c1, Complex& c2) {
		Complex tmp(c1.a - c2.a, c1.b - c2.b);
		return tmp;
	}

private:
	T a;
	T b;

};

int main() {
	Complex<int> c1(1, 4);
	Complex<int> c2(3, 6);
	c1.print();
	c2.print();

	Complex<int> c3 = c1 + c2;
	cout << c3 << endl;

	Complex<int> c4 = sub(c1, c2);
	cout << c4 << endl;
	return 0;
}