/**
 * 1. ʹ�ó�Ա��������Ԫ����ʵ�ֶ�Ԫ������������
 * 2. ����ʹ����Ԫ�����⣬������ʹ��ȫ�ֺ�������ͨ��������ʵ�ֲ����������أ���ͬ����ʹ����Ԫ���������㣬����ֱ�ӷ����������˽�У�private����Ա�ͱ�����protected����Ա
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
	// ʹ�����Ա������� "-" ������������
	Complex operator-(Complex& c2) {
		Complex c3(this->a - c2.a, this->b - c2.b);
		return c3;
	}

	// �������� "+" ���������ص���Ԫ����
	friend Complex operator+(Complex& c1, Complex& c2);
};

// ������Ԫ������� "+" ������������
Complex operator+(Complex& c1, Complex& c2) {
	Complex c3(c1.a + c2.a, c1.b + c2.b);
	return c3;
}

int main() {
	Complex c1(1, 2), c2(3, 4);

	// ֱ�ӵ�����Ԫ����
	Complex c3 = operator+(c1, c2);
	c3.print();

	// ʹ����Ԫ������� "+" ������������
	Complex c4 = c1 + c2;
	c4.print();

	// ֱ�ӵ������Ա����
	Complex c5 = c1.operator-(c2);
	c5.print();

	// ʹ�����Ա������� "-" ������������
	Complex c6 = c1 - c2;
	c6.print();

	return 0;
}