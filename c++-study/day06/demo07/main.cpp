/**
 * 1. 多继承的简单应用
 */

#include <iostream>

using namespace std;

class Base1 {

public:
	Base1(int a) {
		this->a = a;
	}

	void printA() {
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

	void printB() {
		cout << "b = " << b << endl;
	}

private:
	int b;
};

class Base3 : public Base1, public Base2 {

public:
	Base3(int a, int b, int c) : Base1(a), Base2(b) {
		this->c = c;
	}

	void printC() {
		cout << "c = " << c << endl;
	}

private:
	int c;
};

int main() {
	Base3 base(1, 2, 3);
	base.printA();
	base.printB();
	base.printC();
	return 0;
}
