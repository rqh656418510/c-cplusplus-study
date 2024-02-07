/**
 * 1. 虚继承的简单应用
 */

#include <iostream>

using namespace std;

class Base {

public:
	Base(int x) {
		this->x = x;
		cout << "Base 类的构造函数被调用" << endl;
	}

	void printX() {
		cout << "x = " << x << endl;
	}

private:
	int x;
};

// 声明虚继承
class Base1 : virtual  public Base {

public:
	Base1(int a, int x) : Base(x) {
		this->a = a;
	}

	void printA() {
		cout << "a = " << a << endl;
	}

private:
	int a;
};

// 声明虚继承
class Base2 : virtual public Base {

public:
	Base2(int b, int x) : Base(x) {
		this->b = b;
	}

	void printB() {
		cout << "b = " << b << endl;
	}

private:
	int b;
};

class Base3 : public Base1, public Base2 {

public:
	// 由于父类和虚基类没有默认的无参构造函数，所以这里的派生类需要在初始化列表中，显式调用父类、虚基类的有参构造函数
	Base3(int a, int b, int c, int x) : Base1(a, x), Base2(b, x), Base(x) {
		this->c = c;
	}

	void printC() {
		cout << "c = " << c << endl;
	}

private:
	int c;
};

int main() {
	Base3 base(1, 2, 3, 4);  // 虚基类Base的构造函数只会被调用一次
	base.printA();
	base.printB();
	base.printC();
    base.printX();	// 当不声明虚继承的时候，此写法会产生二义性，C++编译器会出现编译错误
	return 0;
}