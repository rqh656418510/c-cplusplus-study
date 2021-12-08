/**
 * 1. 继承与组合对象混搭使用的情况下，构造函数和析构函数的调用原则
 * a) `构造函数的调用`：先构造父类，再构造成员变量，最后构造自身
 * b) `析构函数的调用`：先析构自身，再析构成员变量，最后析构父类
 */

#include <iostream>

using namespace std;

class Object {

public:
	Object(int a, int b) {
		this->a = a;
		this->b = b;
		cout << "Object类的构造函数被调用" << endl;
	}

	~Object() {
		cout << "Object类的析构函数被调用" << endl;
	}

	void printObject() {
		cout << "I'm object, a = " << this->a << ", b = " << this->b << endl;
	}

protected:
	int a;
	int b;
};

class Parent : public Object {

public:

	// 通过初始化列表，调用父类的构造函数
	Parent(char* p) : Object(1, 2) {
		this->p = p;
		cout << "Parent类的构造函数被调用" << endl;
	}

	~Parent() {
		cout << "Parent类的析构函数被调用" << endl;
	}

	void printParent() {
		cout << "I'm parent, p = " << p << endl;
	}

protected:
	char* p;
};

class Child : public Parent {

public:

	// 通过初始化列表，调用组合对象与父类的构造函数
	Child(char* c) : obj1(3, 4), obj2(5, 6), Parent(c) {
		this->c = c;
		cout << "Child类的构造函数被调用" << endl;
	}

	~Child() {
		cout << "Child类的析构函数被调用" << endl;
	}

	void printChild() {
		cout << "I'm child, p = " << p << endl;
	}

protected:
	char* c;

	// 组合对象
	Object obj1;
	Object obj2;
};

int main() {
	char* str = new char[3];
	str[0] = 'J';
	str[1] = 'i';
	str[2] = 'm';

	Child c1(str);
	c1.printChild();
	c1.printParent();
	c1.printObject();

	return 0;
}