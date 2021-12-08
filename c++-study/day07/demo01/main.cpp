/**
 * 1. ֤���麯����ָ�� VPTR �Ĵ���
 */

#include <iostream>

using namespace std;

class Parent1 {
public:
	Parent1(int a) {
		this->a = a;
	}

	// �������麯��
	void print() {
		cout << "I'm parent1" << endl;
	}

private:
	int a;
};

class Parent2 {
public:
	Parent2(int a) {
		this->a = a;
	}

	// �����麯��
	virtual void print() {
		cout << "I'm parent2" << endl;
	}

private:
	int a;
};

int main() {
	// ����ָ��Ҳ��һ���������ͣ�������Parent2�����������麯������Parent2�������VPTRָ�룬��ô����������Ĵ�СӦ���ǲ�һ����
	cout << "sizeof(Parent1): " << sizeof(Parent1) << endl;
	cout << "sizeof(Parent2): " << sizeof(Parent2) << endl;
	return 0;
}