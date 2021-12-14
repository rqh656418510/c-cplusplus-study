/**
 * 1. 函数重写的应用
 */

#include <iostream>

using namespace std;

class Parent {

public:
	Parent(int a) {
		this->a = a;
	}

	void print() {
		cout << "I'm parent, a = " << a << endl;
	}

private:
	int a;
};

class Child : public Parent {
public:

	Child(int a, int c) : Parent(a) {
		this->c = c;
	}

	// 子类重写父类中的函数
	void print() {
		cout << "I'm child, c = " << c << endl;
	}

private:
	int c;
};

int main() {
	Child child(3, 7);

	// 执行子类的函数，默认情况下子类中重写的函数将隐藏父类中的函数
	child.print();

	// 执行父类的函数，通过作用域分辨符"::"可以访问到父类中被隐藏的函数
	child.Parent::print();

	return 0;
}
