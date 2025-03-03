/**
 * shared_ptr 的交叉引用（循环引用）问题
 */

#include <iostream>

using namespace std;

// 解決 shared_ptr 智能指针的循环引用问题

class B;

class A {

public:
	A() {
		cout << "A()" << endl;
	}

	~A() {
		cout << "~A()" << endl;
	}

	// 引用对象时，使用弱引用智能指针
	weak_ptr<B> _ptrB;

};

class B {

public:
	B() {
		cout << "B()" << endl;
	}

	~B() {
		cout << "~B()" << endl;
	}

	// 引用对象时，使用弱引用智能指针
	weak_ptr<A> _ptrA;
};

int main() {
	// 定义对象时，使用强引用智能指针
	shared_ptr<A> ptrA(new A());
	shared_ptr<B> ptrB(new B());

	// 这里不会造成智能指针循环引用的问题
	ptrA->_ptrB = ptrB;
	ptrB->_ptrA = ptrA;

	// 打印智能指针的引用计数
	cout << ptrA.use_count() << endl;
	cout << ptrB.use_count() << endl;
	
	return 0;
}