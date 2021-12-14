/**
 * 1. ��ļ̳�
 */

#include <iostream>

using namespace std;

// ������ࣨ���ࣩ
class Parent {

public:
	Parent(int a = 0, int b = 0) {
		this->a = a;
		this->b = b;
	}

	void print() {
		cout << "a=" << this->a << ", b=" << this->b << endl;
	}

public:
	int a;
	int b;
};

// ���������ࣨ���ࣩ
class Child : public Parent {

public:

	Child(int a = 0, int b = 0, int c = 0) {
		// ֱ�ӷ��ʻ��ࣨ���ࣩ�ĳ�Ա����
		this->a = a;
		this->b = b;
		this->c = c;
	}

	void echo() {
		cout << "a=" << this->a << ", b=" << this->b << ", c=" << this->c << endl;
	}

private:
	int c;
};

int main() {
	Child child(1, 2, 3);
	child.print();	// ֱ�ӵ��û��ࣨ���ࣩ�ĳ�Ա����
	child.echo();	// ֱ�ӵ��������ࣨ���ࣩ�ĳ�Ա����
	return 0;
}
