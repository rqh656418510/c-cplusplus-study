/*
 * 1. 类模板与派生类
 * a) 类模板继承类模板
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

// 模板声明
template <typename T>

// 类模板继承类模板
class B : public A<T> {

public:
	B(T a, T b) : A(a) {
		this->b = b;
	}

	T& getB() {
		return this->b;
	}

private:
	T b;

};

int main() {
	A<int> a(3);
	cout << a.getA() << endl;

	B<double> b(3.2, 4.5);
	cout << b.getA() << endl;
	cout << b.getB() << endl;

	return 0;
}