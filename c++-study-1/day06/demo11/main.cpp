/**
 * 1. 类型兼容原则遇上函数重写时出现的现象
 * a) 当类型兼容原则遇上函数重写，执行以下代码后会出现意外的现象，即被调用的永远是父类的函数
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

	Child(int c) : Parent(c) {
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
	Parent* p = NULL;
	Parent parent(6);
	Child child(5);

	// 执行父类的函数
	p = &parent;
	p->print();

	// 执行父类的函数
	p = &child;
	p->print();

	return 0;
}
