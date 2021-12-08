/*
 * 1. ��ģ���ʹ��
 * a) ���е���ģ�庯��д������ڲ�
*/

#include <iostream>

using namespace std;

template <typename T>

class Complex {

public:

	// ���캯��
	Complex(T a, T b) {
		this->a = a;
		this->b = b;
	}

	// ���Ա����
	void print() {
		cout << "a = " << this->a << ", b = " << this->b << endl;
	}

	// ���Ա��������������� "+"
	Complex operator+(Complex& c2) {
		Complex tmp(this->a + c2.a, this->b + c2.b);
		return tmp;
	}

	// ��Ԫ��������������� "<<"
	friend ostream& operator<<(ostream& out, Complex& c1) {
		cout << "a = " << c1.a << ", b = " << c1.b;
		return out;
	}

	// ��Ԫ����
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