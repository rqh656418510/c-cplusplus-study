/*
 * 1. �쳣�������
 * a) �쳣��ʹ�ð���һ
*/

#include <iostream>

using namespace std;

int divide(int x, int y) {
	if (0 == y) {
		throw y;	// �׳� int ���͵��쳣
	}
	return x / y;
}

int main() {
	try {
		int result = divide(5, 0);
		cout << "result = " << result << endl;
	}
	catch (int e) {
		cout << e << ", ����������Ϊ��" << endl;
	}
	// �Ჶ������δ��������쳣������������
	catch (...) {
		throw "����δ֪���쳣 ...";
	}

	cout << "����������������" << endl;
	return 0;
}