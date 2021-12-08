/*
 * 1. ��ģ����������
 * a) ��ͨ��̳���ģ��
*/

#include <iostream>

using namespace std;

// ģ������
template <typename T>

// �ඨ��
class A {

public:

	A(T a) {
		this->a = a;
	}

	T& getA() {
		return this->a;
	}

public:
	T a;

};

// ��ͨ��̳���ģ�壬��Ҫ������������ͣ�ģ������б�������� <int> ����ʡ��
class B : public A<int> {

public:
	B(int a, int b) : A<int>(a) {
		this->b = b;
	}

	void printB() {
		cout << "a = " << a << ", b = " << b << endl;
	}

public:
	int b;

};

int main() {
	A<int> a(100);
	cout << a.getA() << endl;

	B b(1, 3);
	b.printB();

	return 0;
}