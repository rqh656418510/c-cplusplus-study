/*
 * 1. ����ģ������ͨ����
*/

#include <iostream>

using namespace std;

template <typename T>

void myswap(T& a, T& b) {
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
	cout << "ģ�庯��������" << endl;
}

void myswap(int a, char b) {
	cout << "a = " << a << ", b = " << b << endl;
	cout << "��ͨ����������" << endl;
}

int main() {
	int a = 10;
	char c = 'z';
	myswap(a, c); // ������ͨ����
	myswap(c, a); // ������ͨ�������������ʽ������ת��
	myswap(a, a); // ���ú���ģ�壨���������Ͳ������������ϸ�ذ������ͽ���ƥ�䣬�����Զ���������ת��
	return 0;
}