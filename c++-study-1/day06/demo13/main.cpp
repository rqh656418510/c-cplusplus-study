/**
 * 1. 虚析构函数的简单应用
 * a) 虚析构函数的作用：为了避免内存泄漏，通过父类的指针，可以将所有子类对象的析构函数都执行一遍（释放所有的子类资源）
 * b) 即虚析构函数使得在删除指向子类对象的父类指针时，可以调用子类的析构函数来实现释放子类中堆内存的目的，从而防止内存泄漏
 */

#include <iostream>

using namespace std;

class A {

public:
	A() {
		this->p = new char[20];
		strcpy(p, "Hello A");
		cout << "A 类的构造函数被调用" << endl;
	}

	virtual ~A() {
		delete[] this->p;
		cout << "A 类的析构函数被调用" << endl;
	}

private:
	char* p;
};


class B : public A {

public:
	B() {
		this->p = new char[20];
		strcpy(p, "Hello B");
		cout << "B 类的构造函数被调用" << endl;
	}

	~B() {
		delete[] this->p;
		cout << "B 类的析构函数被调用" << endl;
	}

private:
	char* p;
};

int main() {
	// 此写法，如果上面不使用 "virtual" 修饰A类（基类）的析构函数，派生类与所有基类的析构函数依然都会被自动调用一次
	B* b = new B();
	delete b;

	cout << endl;

	// 此写法，如果上面不使用 "virtual" 修饰A类（基类）的析构函数，那么只有A类（基类）的析构函数会被调用一次，B类（派生类）的析构函数不会被调用，这样就会造成内存泄漏
	// 虚析构函数的作用是，通过父类的指针，可以将所有子类对象的析构函数都执行一遍（释放所有的子类资源）。
	A* a = new B();
	delete a;
	return 0;
}