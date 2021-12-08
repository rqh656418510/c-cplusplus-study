/*
 * 1. 类模板的使用
 * a) 所有的类模板函数写在类的外部（同一个.cpp文件）
*/

#include <iostream>

using namespace std;

/********** START 解决类模板与友元函数滥用（非重载左移与右移运算符）时出现的编译问题 *********/

template <typename T> class Complex;

template <typename T> Complex<T> sub(Complex<T>& c1, Complex<T>& c2);

/********** END 解决类模板与友元函数滥用（非重载左移与右移运算符）时出现的编译问题 *********/

template <typename T>
class Complex {

public:
public:
	// 构造函数
	Complex(T a, T b);
	// 类成员函数
	void print();
	// 类成员函数，重载运算符 "+"
	Complex operator+(Complex& c2);
	// 友元函数（滥用友元函数）
	friend Complex sub<T>(Complex& c1, Complex& c2);
	// 友元函数，重载运算符 "<<"
	friend ostream& operator<< <T>(ostream& out, Complex& c1);

private:
	T a;
	T b;

};

// 构造函数
template <typename T>
Complex<T>::Complex(T a, T b) {
	this->a = a;
	this->b = b;
}

// 类成员函数
template <typename T>
void Complex<T>::print() {
	cout << "a = " << this->a << ", b = " << this->b << endl;
}

// 类成员函数，重载运算符 "+"
template <typename T>
Complex<T> Complex<T>::operator+(Complex<T>& c2) {
	Complex<T> tmp(this->a + c2.a, this->b + c2.b);
	return tmp;
}

// 友元函数，重载运算符 "<<"
template <typename T>
ostream& operator<<(ostream& out, Complex<T>& c1) {
	cout << "a = " << c1.a << ", b = " << c1.b;
	return out;
}

// 友元函数（滥用友元函数）
template <typename T>
Complex<T> sub(Complex<T>& c1, Complex<T>& c2) {
	Complex<T> tmp(c1.a - c2.a, c1.b - c2.b);
	return tmp;
}

int main() {
	Complex<int> c1(3, 8);
	Complex<int> c2(9, 5);
	c1.print();
	c2.print();

	Complex<int> c3 = c1 + c2;
	cout << c3 << endl;

	Complex<int> c4 = sub(c1, c2);
	cout << c4 << endl;

	return 0;
}