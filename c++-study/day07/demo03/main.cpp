/*
 * 1. 父类指针和子类指针的步长可能是不一样的
 * a) 指针也只一种数据类型，对 C++ 类对象的指针执行 `++`、`--` 运算符仍然是合法的
 * b) "多态是用父类的指针指向子类的对象" 和 "父类指针步长的自加（++）" 是两个完全不同的概念
 * c) 当子类继承父类后，没有添加任何自己的成员变量和成员函数，那么此时父类指针和子类指针的步长才是一样的
 * d) 指针运算是按照指针所指的类型进行的，父类指针和子类指针的步长可能是不一样的，不要用父类指针自加（`++`）、自减（`--`）的方式来操作子类的对象数组
 */

#include <iostream>
using namespace std;

class Parent
{
public:
	Parent(int a = 0)
	{
		this->a = a;
	}

	virtual void print()
	{
		cout << "I'm parent" << endl;
	}

private:
	int a;
};

class Child : public Parent
{
public:

	Child(int b, int c) :Parent(0)
	{
		this->b = b;
		this->c = c;
	}

	virtual void print()
	{
		cout << "I'm child" << endl;
	}
private:
	int b;
	int c;
};

int main()
{
	Parent* parent = NULL;
	Child* child = NULL;

	Child  array[] = { Child(1, 2), Child(3,4), Child(5, 6) };
	parent = array;
	child = array;

	// 指针自加运算后运行可能会出错，这里父类指针和子类指针的步长是不一样的，不要用父类指针自加（`++`）、自减（`--`）的方式来操作子类的对象数组
	parent++;
	child++;

	parent++;
	child++;

	return 0;
}