/**
 * 1. ���麯���ͳ������ڶ�̳��е�Ӧ�ð���
 * a) C++ ��û�� Java �еĽӿڸ��������ͨ�����麯���ͳ�����ģ�� Java �еĽӿ�
 */

#include <iostream>

using namespace std;

// ����ӿ���һ
class Interface1 {

public:
	virtual int add(int a, int b) = 0;
	virtual void print() = 0;
};

// ����ӿ����
class Interface2 {

public:
	virtual int mult(int a, int b) = 0;
	virtual void print() = 0;
};

// ���常��
class Parent {

public:
	Parent() {
		this->a = 8;
	}

	virtual ~Parent() {

	}

	virtual int getA() {
		return a;
	}

private:
	int a;
};

// �������࣬���ȼ̳и��࣬Ȼ��̳ж���ӿ���
class Child : public Parent, public Interface1, public Interface2 {

public:
	int add(int a, int b) {
		return a + b;
	}

	int mult(int a, int b) {
		return a * b;
	}

	void print() {
		cout << "Child::print() ������ִ��" << endl;
	}

};

int main() {
	Child child;
	child.print();

	Parent* parent = &child;
	cout << "a = " << parent->getA() << endl;

	Interface1* interface1 = &child;
	int result1 = interface1->add(2, 5);
	cout << "2 + 5 = " << result1 << endl;

	Interface2* interface2 = &child;
	int result2 = interface2->mult(3, 6);
	cout << "3 * 6 = " << result2 << endl;

	return 0;
}