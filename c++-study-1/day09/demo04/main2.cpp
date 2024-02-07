/*
 * 1. 类模板与派生类
 * a) 普通类继承类模板
*/

#include <iostream>

using namespace std;

// 模板声明
template <typename T>

// 类定义
class A {

public:

	A(T a) {
		this->a = a;
	}

	T& getA() {
		return this->a;
	}

public:
	T a;

};

// 普通类继承类模板，需要声明具体的类型（模板参数列表），这里的 <int> 不能省略
class B : public A<int> {

public:
	B(int a, int b) : A<int>(a) {
		this->b = b;
	}

	void printB() {
		cout << "a = " << a << ", b = " << b << endl;
	}

public:
	int b;

};

int main() {
	A<int> a(100);
	cout << a.getA() << endl;

	B b(1, 3);
	b.printB();

	return 0;
}