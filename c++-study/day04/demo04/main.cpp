/**
 * 1. 友元类的使用
 */

#include <iostream>

using namespace std;

class A {

public:

	// 声明友元类 B
	friend class B;

	void print() {
		cout << "a = " << a << endl;
	}

private:
	int a;
};

class B {

public:
	void setValue(int a) {
		aObj.a = a;		// 类 B 是类 A 的友元类，因此 B 类的所有成员函数都可以访问 A 类的私有成员或者保护成员
	}

	void print() {
		aObj.print();
	}

private:
	A aObj;

};

int main() {
	B b;
	b.setValue(100);
	b.print();
	return 0;
}