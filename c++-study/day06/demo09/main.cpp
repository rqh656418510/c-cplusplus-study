/**
 * 1. ��̳н�����˵�����
 */

#include <iostream>

using namespace std;

class Base1 {

public:
	Base1(int a) {
		this->a = a;
	}

	void print() {
		cout << "a = " << a << endl;
	}

private:
	int a;
};

class Base2 {

public:
	Base2(int b) {
		this->b = b;
	}

	void print() {
		cout << "b = " << b << endl;
	}

private:
	int b;
};

class Base3 : virtual public Base1, virtual public Base2 {

public:
	Base3(int a, int b) : Base1(a), Base2(b) {

	}
};

int main() {
	Base3 base(1, 2);

	// ��̳�ֻ�������й�ͬ���ࣨ�������ࣩ�Ķ�̳г�������ʯ���� ��
	// ���� `V` ���εĶ�̳г������������£�����̳���û�취��������������
	// ��ʹ������������̳У�����д����Ȼ����������ԣ�C++����������ֱ������
	// base.print();

	base.Base1::print();
	base.Base2::print();

	return 0;
}
