/*
 * 1. ����ģ���ʹ��
*/

#include <iostream>

using namespace std;

// ģ������
template <typename T>

// ��������
void myswap(T& a, T& b) {
	T temp;
	temp = a;
	a = b;
	b = temp;
}

int main() {

	// �Զ����������Ƶ�
	int x = 1, y = 2;
	myswap(x, y);
	printf("x = %d, y = %d\n", x, y);

	// �Զ����������Ƶ�
	double n = 0.5, m = 0.8;
	myswap(n, m);
	printf("n = %f, m = %f\n", n, m);

	// ��ʾ���͵��ã��Ƽ���
	char i = 'h', j = 'e';
	myswap<char>(i, j);
	printf("n = %c, m = %c\n", i, j);

	return 0;
}