/**
 * 1. 纯虚函数和抽象类在多继承中的应用案例
 * a) C++ 中没有 Java 中的接口概念，但可以通过纯虚函数和抽象类模拟 Java 中的接口
 */

#include <iostream>

using namespace std;

// 定义接口类一
class Interface1 {

public:
	virtual int add(int a, int b) = 0;
	virtual void print() = 0;
};

// 定义接口类二
class Interface2 {

public:
	virtual int mult(int a, int b) = 0;
	virtual void print() = 0;
};

// 定义父类
class Parent {

public:
	Parent() {
		this->a = 8;
	}

	virtual ~Parent() {

	}

	virtual int getA() {
		return a;
	}

private:
	int a;
};

// 定义子类，首先继承父类，然后继承多个接口类
class Child : public Parent, public Interface1, public Interface2 {

public:
	int add(int a, int b) {
		return a + b;
	}

	int mult(int a, int b) {
		return a * b;
	}

	void print() {
		cout << "Child::print() 函数被执行" << endl;
	}

};

int main() {
	Child child;
	child.print();

	Parent* parent = &child;
	cout << "a = " << parent->getA() << endl;

	Interface1* interface1 = &child;
	int result1 = interface1->add(2, 5);
	cout << "2 + 5 = " << result1 << endl;

	Interface2* interface2 = &child;
	int result2 = interface2->mult(3, 6);
	cout << "3 * 6 = " << result2 << endl;

	return 0;
}