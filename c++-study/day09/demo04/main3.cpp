/*
 * 1. ��ģ����������
 * a) ��ģ��̳���ģ��
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

// ģ������
template <typename T>

// ��ģ��̳���ģ��
class B : public A<T> {

public:
	B(T a, T b) : A(a) {
		this->b = b;
	}

	T& getB() {
		return this->b;
	}

private:
	T b;

};

int main() {
	A<int> a(3);
	cout << a.getA() << endl;

	B<double> b(3.2, 4.5);
	cout << b.getA() << endl;
	cout << b.getB() << endl;

	return 0;
}