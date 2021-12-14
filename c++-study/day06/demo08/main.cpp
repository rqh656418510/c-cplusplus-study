/**
 * 1. ��̳еļ�Ӧ��
 */

#include <iostream>

using namespace std;

class Base {

public:
	Base(int x) {
		this->x = x;
		cout << "Base ��Ĺ��캯��������" << endl;
	}

	void printX() {
		cout << "x = " << x << endl;
	}

private:
	int x;
};

// ������̳�
class Base1 : virtual  public Base {

public:
	Base1(int a, int x) : Base(x) {
		this->a = a;
	}

	void printA() {
		cout << "a = " << a << endl;
	}

private:
	int a;
};

// ������̳�
class Base2 : virtual public Base {

public:
	Base2(int b, int x) : Base(x) {
		this->b = b;
	}

	void printB() {
		cout << "b = " << b << endl;
	}

private:
	int b;
};

class Base3 : public Base1, public Base2 {

public:
	// ���ڸ���������û��Ĭ�ϵ��޲ι��캯���������������������Ҫ�ڳ�ʼ���б��У���ʽ���ø��ࡢ�������вι��캯��
	Base3(int a, int b, int c, int x) : Base1(a, x), Base2(b, x), Base(x) {
		this->c = c;
	}

	void printC() {
		cout << "c = " << c << endl;
	}

private:
	int c;
};

int main() {
	Base3 base(1, 2, 3, 4);  // �����Base�Ĺ��캯��ֻ�ᱻ����һ��
	base.printA();
	base.printB();
	base.printC();
    base.printX();	// ����������̳е�ʱ�򣬴�д������������ԣ�C++����������ֱ������
	return 0;
}