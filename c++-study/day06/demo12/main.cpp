/**
 * 1. �麯����Ӧ��
 * a) ���ͼ���ԭ�����Ϻ�����дʱ�Ľ������
 */

#include <iostream>

using namespace std;

class Parent {

public:
	Parent(int a) {
		this->a = a;
	}

	// ʹ�� "virtual" �ؼ�����������ĺ���
	virtual void print() {
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

	// ʹ�� "virtual" �ؼ���������д�����еĺ���
	// ֻҪ�����еĺ����� "virtual" �ؼ��ֵ���������ô����� "virtual" ������д�ɲ�д��һ�㽨�鶼д��
	virtual void print() {
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

	// ִ������ĺ���
	p = &child;
	p->print();

	return 0;
}
