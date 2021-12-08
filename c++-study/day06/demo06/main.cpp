/**
 * 1. �������е� static �ؼ���ʹ��
 * a) ���ඨ��ľ�̬��Ա���������������๲��
 * b) ���ݾ�̬��Ա����ķ������Ժ�������ļ̳з�ʽ����������ϵ�о��в�ͬ�ķ������ʣ������������Ա���ʼ�����Ƶ�ԭ��
 * c) ���������з��ʻ���ľ�̬��Ա��Ҫ�����µ���ʽ��ʽ˵����`���� :: ��Ա` ����ͨ��������ʣ�`������ . ��Ա`
 */

#include <iostream>

using namespace std;

class Parent {

public:
	// �������еľ�̬��Ա����
	static void print() {
		cout << "a = " << a << ", b = " << b << endl;
	}

public:
	// �������еľ�̬��Ա����
	static int a;

private:
	// ����˽�еľ�̬��Ա����
	static int b;
};

// ����˽�еľ�̬��Ա����
int Parent::b = 50;

// ���幫�еľ�̬��Ա���������ﲻ�Ǽ򵥵ı�����ֵ������Ҫ���Ǹ���C++������������̬��Ա���������ڴ�, ���������������õ��ñ����ͻᱨ��
int Parent::a = 30;

class Child : public Parent {

public:
	int getA() {
		// ���ʴӻ���̳еõ��ľ�̬��Ա����
		return this->a;
	}

	int getA2() {
		// ���ʻ���ľ�̬��Ա����
		return Parent::a;
	}

	int getB() {
		// return b;  ����д���������о�̬��Ա����ķ�����������������ķ��ʼ������ԭ��������ﲻ�ܷ��ʻ�����˽�еľ�̬��Ա����b
		return 0;
	}

	// ���ôӻ���̳еõ��ľ�̬��Ա����
	void print2() {
		this->print();
	}

	// ���û���ľ�̬��Ա����
	void print1() {
		Parent::print();
	}
};

int main() {
	
	// ��������ʻ���ľ�̬��Ա�����;�̬��Ա����
	Parent::a++;
	Parent::print();
	cout << endl;

	// ���������������ľ�̬��Ա�����;�̬��Ա����
	cout << "a = " << Child::a << endl;
	Child::print();
	cout << endl;

	Child c1;

	cout << "a = " << c1.getA() << endl;
	cout << "a = " << c1.getA2() << endl;
	cout << "a = " << c1.Parent::a << endl;
	cout << endl;
	
	c1.print1();
	c1.print2();
	c1.Parent::print();

	return 0;
}