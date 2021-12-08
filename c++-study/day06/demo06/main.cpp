/**
 * 1. 派生类中的 static 关键字使用
 * a) 基类定义的静态成员，将被所有派生类共享
 * b) 根据静态成员自身的访问特性和派生类的继承方式，在类层次体系中具有不同的访问性质（遵守派生类成员访问级别控制的原则）
 * c) 在派生类中访问基类的静态成员，要用以下的形式显式说明：`类名 :: 成员` 或者通过对象访问：`对象名 . 成员`
 */

#include <iostream>

using namespace std;

class Parent {

public:
	// 声明公有的静态成员函数
	static void print() {
		cout << "a = " << a << ", b = " << b << endl;
	}

public:
	// 声明公有的静态成员变量
	static int a;

private:
	// 声明私有的静态成员变量
	static int b;
};

// 定义私有的静态成员变量
int Parent::b = 50;

// 定义公有的静态成员变量，这里不是简单的变量赋值，更重要的是告诉C++编译器，给静态成员变量分配内存, 否则在派生类中用到该变量就会报错
int Parent::a = 30;

class Child : public Parent {

public:
	int getA() {
		// 访问从基类继承得到的静态成员变量
		return this->a;
	}

	int getA2() {
		// 访问基类的静态成员变量
		return Parent::a;
	}

	int getB() {
		// return b;  错误写法，基类中静态成员自身的访问特性遵守派生类的访问级别控制原则，因此这里不能访问基类中私有的静态成员变量b
		return 0;
	}

	// 调用从基类继承得到的静态成员函数
	void print2() {
		this->print();
	}

	// 调用基类的静态成员函数
	void print1() {
		Parent::print();
	}
};

int main() {
	
	// 在类外访问基类的静态成员变量和静态成员函数
	Parent::a++;
	Parent::print();
	cout << endl;

	// 在类外访问派生类的静态成员变量和静态成员函数
	cout << "a = " << Child::a << endl;
	Child::print();
	cout << endl;

	Child c1;

	cout << "a = " << c1.getA() << endl;
	cout << "a = " << c1.getA2() << endl;
	cout << "a = " << c1.Parent::a << endl;
	cout << endl;
	
	c1.print1();
	c1.print2();
	c1.Parent::print();

	return 0;
}