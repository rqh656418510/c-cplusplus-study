/**
 * 1. ��֤�ڸ���Ĺ��캯�����ܵ����麯�����Ƿ����ʵ�ֶ�̬
 * a) ����������� VPTR ָ���Ƿֲ���ɳ�ʼ���ģ���ִ�и���Ĺ��캯��ʱ������ �� VPTR ָ��ָ������麯����������Ĺ��캯��ִ����Ϻ󣬲Ż������� VPTR ָ��ָ��������麯����
 * b) ���ۣ��ڸ���Ĺ��캯���е����麯��������ʵ�ֶ�̬
 */

#include <iostream>

using namespace std;

class Parent {

public:
	Parent(int a) {
		this->a = a;
		// �ڸ���Ĺ��캯���е����麯��
		print();
	}

	virtual void print() {
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

	virtual void print() {
		cout << "I'm child, c = " << c << endl;
	}

private:
	int c;
};

int main() {
	Child child(5, 8);
	return 0;
}
