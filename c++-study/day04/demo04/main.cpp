/**
 * 1. ��Ԫ���ʹ��
 */

#include <iostream>

using namespace std;

class A {

public:

	// ������Ԫ�� B
	friend class B;

	void print() {
		cout << "a = " << a << endl;
	}

private:
	int a;
};

class B {

public:
	void setValue(int a) {
		aObj.a = a;		// �� B ���� A ����Ԫ�࣬��� B ������г�Ա���������Է��� A ���˽�г�Ա���߱�����Ա
	}

	void print() {
		aObj.print();
	}

private:
	A aObj;

};

int main() {
	B b;
	b.setValue(100);
	b.print();
	return 0;
}