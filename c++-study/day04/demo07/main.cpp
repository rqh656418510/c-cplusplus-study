/**
 * 1. ʹ����Ԫ����ʵ�����Ʋ�����������
 * 2. ��<<�� ����������� ��>>�� ��������������أ�ֻ��ʹ����Ԫ��������ȫ�ֺ���������ʹ�����Ա��������Ҳ����Ԫ��������Ҫ����֮һ
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
	// ������Ԫ����ʵ�� "<<" ���Ʋ�����������
	friend ostream& operator<<(ostream& out, Complex& c1);
};

// ������Ԫ����ʵ�� "<<" ���Ʋ�����������
ostream& operator<<(ostream& out, Complex& c1) {
	out << "a=" << c1.a << ", b=" << c1.b << endl;
	return out;
}

int main() {
	Complex c1(1, 2), c2(6, 9);
	cout << c1 << c2;
	return 0;
}