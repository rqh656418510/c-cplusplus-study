/**
 * 1. �̳�����϶�����ʹ�õ�����£����캯�������������ĵ���ԭ��
 * a) `���캯���ĵ���`���ȹ��츸�࣬�ٹ����Ա���������������
 * b) `���������ĵ���`��������������������Ա�����������������
 */

#include <iostream>

using namespace std;

class Object {

public:
	Object(int a, int b) {
		this->a = a;
		this->b = b;
		cout << "Object��Ĺ��캯��������" << endl;
	}

	~Object() {
		cout << "Object�����������������" << endl;
	}

	void printObject() {
		cout << "I'm object, a = " << this->a << ", b = " << this->b << endl;
	}

protected:
	int a;
	int b;
};

class Parent : public Object {

public:

	// ͨ����ʼ���б����ø���Ĺ��캯��
	Parent(char* p) : Object(1, 2) {
		this->p = p;
		cout << "Parent��Ĺ��캯��������" << endl;
	}

	~Parent() {
		cout << "Parent�����������������" << endl;
	}

	void printParent() {
		cout << "I'm parent, p = " << p << endl;
	}

protected:
	char* p;
};

class Child : public Parent {

public:

	// ͨ����ʼ���б�������϶����븸��Ĺ��캯��
	Child(char* c) : obj1(3, 4), obj2(5, 6), Parent(c) {
		this->c = c;
		cout << "Child��Ĺ��캯��������" << endl;
	}

	~Child() {
		cout << "Child�����������������" << endl;
	}

	void printChild() {
		cout << "I'm child, p = " << p << endl;
	}

protected:
	char* c;

	// ��϶���
	Object obj1;
	Object obj2;
};

int main() {
	char* str = new char[3];
	str[0] = 'J';
	str[1] = 'i';
	str[2] = 'm';

	Child c1(str);
	c1.printChild();
	c1.printParent();
	c1.printObject();

	return 0;
}