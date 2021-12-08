/**
 * 1. ʹ�ó�Ա��������Ԫ����ʵ��һԪ������������
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
	// ʹ�����Ա������� "ǰ��--" ������������
	Complex& operator--() {
		this->a--;
		this->b--;
		return *this;
	}

	// ʹ�����Ա������� "����--" ������������
	// ʹ��ռλ�������к������أ���Ϊ�˽���� "ǰ��--" ���Ա������ͻ������
	Complex operator--(int) {
		Complex tmp(this->a, this->b);
		this->a--;
		this->b--;
		return tmp;
	}

	// �������� "ǰ��++" ���������ص���Ԫ����
	friend Complex& operator++(Complex& c1);

	// �������� "����++" ���������ص���Ԫ����
	// ʹ��ռλ�������к������أ���Ϊ�˽���� "ǰ��++" ��Ԫ������ͻ������
	friend Complex operator++(Complex& c1, int);
};

// ������Ԫ������� "ǰ��++" ������������
Complex& operator++(Complex& c1)
{
	c1.a++;
	c1.b++;
	return c1;
}

// ������Ԫ������� "����++" ������������
Complex operator++(Complex& c1, int) {
	Complex tmp(c1.a, c1.b);
	c1.a++;
	c1.b++;
	return tmp;
}

int main() {
	Complex c1(1, 2), c2(8, 9), c3(15, 16), c4(24, 25);

	// ʹ����Ԫ������� "ǰ��++" ������������
	++c1;
	c1.print();

	// ʹ�����Ա������� "ǰ��--" ������������
	--c2;
	c2.print();

	// ʹ����Ԫ������� "����++" ������������
	Complex c5 = c3++;
	c3.print();
	c5.print();

	// ʹ�����Ա������� "����--" ������������
	Complex c6 = c4--;
	c4.print();
	c6.print();

	return 0;
}

