#include "complex.h"

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