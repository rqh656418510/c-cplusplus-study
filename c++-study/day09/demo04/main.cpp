/*
 * 1. ��ģ���ʹ��
 * a) ������ģ���ʹ��
 * b) ��ģ������������
*/

#include <iostream>

using namespace std;

// ģ������
template <typename T>

// �ඨ��
class A {

public:

	A(T t) {
		this->t = t;
	}

	T& getT() {
		return this->t;
	}

private:
	T t;

};

// ��ģ������������
void printA(A<int>& a) {
	cout << a.getT() << endl;
}

int main() {
	A<int> a(100);	// ģ�����ǳ���ģ���Ҫ������������ͣ�ģ������б�������� <int> ����ʡ��
	cout << a.getT() << endl;

	A<int> a2(50);
	printA(a2);

	return 0;
}