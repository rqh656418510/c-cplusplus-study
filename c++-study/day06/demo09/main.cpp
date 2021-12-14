/**
 * 1. 虚继承解决不了的问题
 */

#include <iostream>

using namespace std;

class Base1 {

public:
	Base1(int a) {
		this->a = a;
	}

	void print() {
		cout << "a = " << a << endl;
	}

private:
	int a;
};

class Base2 {

public:
	Base2(int b) {
		this->b = b;
	}

	void print() {
		cout << "b = " << b << endl;
	}

private:
	int b;
};

class Base3 : virtual public Base1, virtual public Base2 {

public:
	Base3(int a, int b) : Base1(a), Base2(b) {

	}
};

int main() {
	Base3 base(1, 2);

	// 虚继承只适用于有共同基类（公共基类）的多继承场景（钻石菱形 ◇）
	// 对于 `V` 字形的多继承场景（代码如下），虚继承是没办法解决二义性问题的
	// 即使上面声明了虚继承，但此写法仍然会产生二义性，C++编译器会出现编译错误
	// base.print();

	base.Base1::print();
	base.Base2::print();

	return 0;
}
