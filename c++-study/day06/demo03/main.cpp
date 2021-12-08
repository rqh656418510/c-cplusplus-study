/**
 * 1. �̳��еĹ��캯�������������ĵ���ԭ��
 * a) ��������ڴ���ʱ�������ȵ��ø���Ĺ��캯��
 * b) ���๹�캯��ִ�н�������ִ������Ĺ��캯��
 * c) ������ֻ�����вι��캯��ʱ������������ĳ�ʼ���б�����ʾ���ø���Ĺ��캯��
 * d) �����������õ��Ⱥ�˳���빹�캯���෴�����ȵ�������������������ٵ��ø������������
 */

#include <iostream>

using namespace std;

class Parent {

public:

	Parent(int a, int b) {
		this->a = a;
		this->b = b;
		cout << "����Ĺ��캯��������" << endl;
	}

	~Parent() {
		cout << "�������������������" << endl;
	}

	void printParent() {
		cout << "I'm parent, a = " << this->a << ", b = " << this->b << endl;
	}

private:
	int a;
	int b;
};

class Child : public Parent {

public:

	// ������ֻ�����вι��캯��ʱ������������ĳ�ʼ���б�����ʾ����
	Child(int a, int b, int c) : Parent(a, b) {
		this->c = c;
		cout << "����Ĺ��캯��������" << endl;
	}

	~Child() {
		cout << "�������������������" << endl;
	}

	void printChild() {
		cout << "I'm child, c = " << this->c << endl;
	}

private:
	int c;
};

int main() {
	Child c1(1, 2, 3);
	c1.printParent();
	c1.printChild();
	return 0;
}