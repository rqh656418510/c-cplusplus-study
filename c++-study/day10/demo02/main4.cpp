/*
 * 1. �쳣�������
 * a) ջ������unwinding��
 * b) �쳣���׳��󣬴ӽ��� try ������𣬵��쳣������ǰ�����ڼ���ջ�Ϲ�������ж��󣬶��ᱻ�Զ�������������˳���빹���˳���෴����һ���̳�Ϊ "ջ������unwinding��"
*/

#include <iostream>

using namespace std;

class Test {

public:
	Test(int a, int b) {
		this->a = a;
		this->b = b;
		cout << "���캯��������" << endl;
	}

	~Test() {
		cout << "��������������" << endl;
	}

private:
	int a;
	int b;
};

int divide(int x, int y) {
	Test t1(3, 4), t2(5, 6);
	if (0 == y) {
		throw y;	// �׳� int ���͵��쳣
	}
	return x / y;
}

int main() {
	// divide(5, 0);  ��� divide() �����ĵ���д�� try �����֮�⣬��ô Test ����������������Զ�������

	try {
		int result = divide(5, 0);
		cout << "result = " << result << endl;
	}
	catch (int e) {
		cout << e << ", ����������Ϊ��" << endl;
	}
	catch (...) {
		cout << "����δ֪���쳣";
	}
	return 0;
}