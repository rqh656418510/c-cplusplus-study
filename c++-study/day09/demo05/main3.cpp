/*
 * 1. ��ģ���ʹ��
 * a) ���е���ģ�庯��д������ⲿ���ڲ�ͬ�� .h �� .cpp �У�
*/

#include "complex.hpp"  // ����������� `.hpp` �ļ��������� `.h` ͷ�ļ������� C++ �����������ʧ��

int main() {
	Complex<int> c1(6, 13);
	Complex<int> c2(23, 34);
	c1.print();
	c2.print();

	Complex<int> c3 = c1 + c2;
	cout << c3 << endl;

	return 0;
}