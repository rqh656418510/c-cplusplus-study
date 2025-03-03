/**
 * shared_ptr 的交叉引用（循环引用）问题
 */

#include <iostream>

using namespace std;

// weak_ptr 智能指针的使用

class B;

class A {

public:
	A() {
		cout << "A()" << endl;
	}

	~A() {
		cout << "~A()" << endl;
	}

	void func() {
		cout << "A::func()" << endl;
		// 必须提升弱引用智能指针为强智能指针，这样才能调用被管理对象的方法
		shared_ptr<B> ptrB = _ptrB.lock();
		if (ptrB != nullptr) {
			ptrB->func();
		}
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

	void func() {
		cout << "B::func()" << endl;
		// 必须提升弱引用智能指针为强智能指针，这样才能调用被管理对象的方法
		shared_ptr<A> ptrA = _ptrA.lock();
		if (ptrA != nullptr) {
			ptrA->func();
		}
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