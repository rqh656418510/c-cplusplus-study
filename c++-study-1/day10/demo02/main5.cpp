/*
 * 1. 异常处理机制
 * a) 异常接口的声明
*/

#include <iostream>

using namespace std;

class A {};
class B {};
class C {};
class D {};
class F {};

// 能够且只能抛出类型 A、B、C、D 及其子类型的异常
void funcA() throw (A, B, C, D) {
	throw A();
}

// 不能抛出任何类型的异常
void funcB() throw() {

}

// 可以抛出任何类型的异常
void funcC() {
	throw B();
}

int main() {
	try {
		funcA();
	}
	catch (...) {
		cout << "发生异常 ..." << endl;
	}
	return 0;
}