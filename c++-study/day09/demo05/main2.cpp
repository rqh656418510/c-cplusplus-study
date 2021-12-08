/*
 * 1. ��ģ���ʹ��
 * a) ���е���ģ�庯��д������ⲿ��ͬһ��.cpp�ļ���
*/

#include <iostream>

using namespace std;

/********** START �����ģ������Ԫ�������ã������������������������ʱ���ֵı������� *********/

template <typename T> class Complex;

template <typename T> Complex<T> sub(Complex<T>& c1, Complex<T>& c2);

/********** END �����ģ������Ԫ�������ã������������������������ʱ���ֵı������� *********/

template <typename T>
class Complex {

public:
public:
	// ���캯��
	Complex(T a, T b);
	// ���Ա����
	void print();
	// ���Ա��������������� "+"
	Complex operator+(Complex& c2);
	// ��Ԫ������������Ԫ������
	friend Complex sub<T>(Complex& c1, Complex& c2);
	// ��Ԫ��������������� "<<"
	friend ostream& operator<< <T>(ostream& out, Complex& c1);

private:
	T a;
	T b;

};

// ���캯��
template <typename T>
Complex<T>::Complex(T a, T b) {
	this->a = a;
	this->b = b;
}

// ���Ա����
template <typename T>
void Complex<T>::print() {
	cout << "a = " << this->a << ", b = " << this->b << endl;
}

// ���Ա��������������� "+"
template <typename T>
Complex<T> Complex<T>::operator+(Complex<T>& c2) {
	Complex<T> tmp(this->a + c2.a, this->b + c2.b);
	return tmp;
}

// ��Ԫ��������������� "<<"
template <typename T>
ostream& operator<<(ostream& out, Complex<T>& c1) {
	cout << "a = " << c1.a << ", b = " << c1.b;
	return out;
}

// ��Ԫ������������Ԫ������
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