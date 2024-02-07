/**
 * 1. 继承中的构造函数与析构函数的调用原则
 * a) 子类对象在创建时，会首先调用父类的构造函数
 * b) 父类构造函数执行结束后，再执行子类的构造函数
 * c) 当父类只存在有参构造函数时，必须在子类的初始化列表中显示调用父类的构造函数
 * d) 析构函数调用的先后顺序与构造函数相反，即先调用子类的析构函数，再调用父类的析构函数
 */

#include <iostream>

using namespace std;

class Parent {

public:

	Parent(int a, int b) {
		this->a = a;
		this->b = b;
		cout << "父类的构造函数被调用" << endl;
	}

	~Parent() {
		cout << "父类的析构函数被调用" << endl;
	}

	void printParent() {
		cout << "I'm parent, a = " << this->a << ", b = " << this->b << endl;
	}

private:
	int a;
	int b;
};

class Child : public Parent {

public:

	// 当父类只存在有参构造函数时，必须在子类的初始化列表中显示调用
	Child(int a, int b, int c) : Parent(a, b) {
		this->c = c;
		cout << "子类的构造函数被调用" << endl;
	}

	~Child() {
		cout << "子类的析构函数被调用" << endl;
	}

	void printChild() {
		cout << "I'm child, c = " << this->c << endl;
	}

private:
	int c;
};

int main() {
	Child c1(1, 2, 3);
	c1.printParent();
	c1.printChild();
	return 0;
}