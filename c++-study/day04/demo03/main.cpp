/**
 * 1. ��Ԫ������ʹ��
 */

#include <iostream>

using namespace std;

class A {
public:
	A(int a) {
		this->a = a;
	}

	int getA() {
		return this->a;
	}

	// ������Ԫ����
	friend void update2(A* p);

private:
	int a;
};

void update1(A* p) {
	// p->a = 30;  // ����д��������ͨ������ȫ�ֺ������ڣ�˽�����ݳ�Ա���������ⱻ����
}

void update2(A* p) {
	p->a = 30;		// ����Ԫ�����ڣ�����ͨ�������������˽�����ݳ�Ա
}

int main() {
	A* a = new A(10);
	update2(a);		// ������Ԫ����
	cout << "a = " << a->getA() << endl;
	delete a;
	return 0;
}