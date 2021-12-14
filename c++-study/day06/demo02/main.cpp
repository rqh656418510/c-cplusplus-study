/**
 * 1. 继承中的类型兼容原则
 * 2. 类型兼容规则是指在需要基类对象的任何地方，都可以使用公有派生类（Public 继承）的对象来替代
 * 3. 通过公有继承，派生类得到了基类中除构造函数、析构函数之外的所有成员。这样，公有派生类实际就具备了基类的所有功能，凡是基类能解决的问题，公有派生类都可以解决
 * 4. 值得一提的是，在替代之后，派生类对象就可以作为基类的对象使用，但是只能使用从基类继承得到的成员，类型兼容规则是多态性的重要基础之一
 */

#include <iostream>

using namespace std;

// 父类
class Parent {

public:
	void printParent() {
		cout << "I'm parent" << endl;
	}

private:
	int a;
};

// 子类（公有继承）
class Child : public Parent {

public:
	void printChild() {
		cout << "I'm child" << endl;
	}

private:
	int c;
};

void howToPrint(Parent* p) {
	p->printParent();
}

void howToPrint(Parent& p) {
	p.printParent();
}

int main() {
	Parent p1;
	p1.printParent();

	Child c1;
	c1.printChild();
	c1.printParent();

	// 1-1 父类指针可以直接指向子类对象
	cout << "1-1" << endl;
	Parent* p2 = NULL;
	p2 = &c1;
	p2->printParent();

	// 1-2 父类指针可以直接指向子类对象，指针做函数参数
	cout << "1-2" << endl;
	howToPrint(&p1);
	howToPrint(&c1);

	// 2-1 父类引用可以直接引用子类对象
	cout << "2-1" << endl;
	Parent& p3 = c1;
	p3.printParent();

	// 2-2 父类引用可以直接引用子类对象，引用做函数参数
	cout << "2-2" << endl;
	howToPrint(p1);
	howToPrint(c1);

	// 3-1 子类对象可以直接初始化父类对象，会自动调用父类的拷贝构造函数
	cout << "3-1" << endl;
	Parent p4 = c1;
	p4.printParent();

	// 4-1 子类对象可以直接赋值给父类对象
	cout << "4-1" << endl;
	Parent p5;
	p5 = c1;
	p5.printParent();

	return 0;
}