/**
 * 1. ���ͼ���ԭ�����Ϻ�����дʱ���ֵ�����
 * a) �����ͼ���ԭ�����Ϻ�����д��ִ�����´����������������󣬼������õ���Զ�Ǹ���ĺ���
 */

#include <iostream>

using namespace std;

class Parent {

public:
	Parent(int a) {
		this->a = a;
	}

	void print() {
		cout << "I'm parent, a = " << a << endl;
	}

private:
	int a;
};

class Child : public Parent {
public:

	Child(int c) : Parent(c) {
		this->c = c;
	}

	// ������д�����еĺ���
	void print() {
		cout << "I'm child, c = " << c << endl;
	}

private:
	int c;
};

int main() {
	Parent* p = NULL;
	Parent parent(6);
	Child child(5);

	// ִ�и���ĺ���
	p = &parent;
	p->print();

	// ִ�и���ĺ���
	p = &child;
	p->print();

	return 0;
}
