/**
 * 1. ������д��Ӧ��
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

	Child(int a, int c) : Parent(a) {
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
	Child child(3, 7);

	// ִ������ĺ�����Ĭ���������������д�ĺ��������ظ����еĺ���
	child.print();

	// ִ�и���ĺ�����ͨ��������ֱ��"::"���Է��ʵ������б����صĺ���
	child.Parent::print();

	return 0;
}
