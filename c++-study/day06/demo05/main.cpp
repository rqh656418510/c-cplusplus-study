/**
 * 1. �̳��е�ͬ����Ա�Ĵ���ʽ
 */

#include <iostream>

using namespace std;

class Parent {

public:
	Parent(int a, int b) {
		this->a = a;
		this->b = b;
	}

	void print() {
		cout << "I'm parent, a = " << a << ", b = " << b << endl;
	}

public:
	int a;
	int b;
};

class Child : public Parent {

public:

	Child(int a, int b) : Parent(a, b) {
		this->a = a + 5;
		this->b = b + 5;
	}

	void print() {
		cout << "I'm child, a = " << a << ", b = " << b << endl;
	}

public:
	int a;
	int b;
};

int main() {
	Child child(1, 2);

	// ������������ͬ����Ա����
	child.print();

	// ������������ͬ����Ա����
	cout << "child's a = " << child.a << endl;
	cout << "child's b = " << child.b << endl;

	// ������ʸ����ͬ����Ա����
	child.Parent::print();

	// ������ʸ����ͬ����Ա����
	cout << "parent's a = " << child.Parent::a << endl;
	cout << "parent's b = " << child.Parent::b << endl;

	return 0;
}
