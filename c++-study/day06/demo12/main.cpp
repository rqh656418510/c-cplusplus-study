/**
 * 1. 虚函数的应用
 * a) 类型兼容原则遇上函数重写时的解决方案
 */

#include <iostream>

using namespace std;

class Parent {

public:
	Parent(int a) {
		this->a = a;
	}

	// 使用 "virtual" 关键字声明父类的函数
	virtual void print() {
		cout << "I'm parent, a = " << a << endl;
	}

private:
	int a;
};

class Child : public Parent {
public:

	Child(int c) : Parent(c) {
		this->c = c;
	}

	// 使用 "virtual" 关键字声明重写父类中的函数
	// 只要父类中的函数有 "virtual" 关键字的声明，那么子类的 "virtual" 声明可写可不写，一般建议都写上
	virtual void print() {
		cout << "I'm child, c = " << c << endl;
	}

private:
	int c;
};

int main() {
	Parent* p = NULL;
	Parent parent(6);
	Child child(5);

	// 执行父类的函数
	p = &parent;
	p->print();

	// 执行子类的函数
	p = &child;
	p->print();

	return 0;
}
