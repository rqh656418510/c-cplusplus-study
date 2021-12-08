/**
 * 1. 全局函数与成员函数的使用
 */

#include <iostream>
using namespace std;

class Test
{
public:
	int a;
	int b;

public:
	Test(int a = 0, int b = 0)
	{
		this->a = a;
		this->b = b;
	}

	~Test()
	{

	}

public:
	void printT()
	{
		cout << "a:" << a << " b: " << b << endl;
	}

	Test testAdd(Test& t2)
	{
		Test tmp(this->a + t2.a, this->b + t2.b);
		return tmp;
	}

	//t1.testAdd2(t2);
	//返回一个引用，相当于返回自身
	//返回t1这个元素，this就是&t1
	Test& testAdd2(Test& t2)
	{
		this->a = this->a + t2.a;
		this->b = this->b + t2.b;
		return *this; //把 *(&t1) 又回到了 t1元素
	}
};

// 全局函数
Test testAdd(Test& t1, Test& t2)
{
	Test tmp;
	tmp.a = t1.a + t2.a;
	tmp.b = t1.b + t2.b;
	return tmp;
}

// 全局函数
void printT(Test* pT)
{
	cout << "a:" << pT->a << " b: " << pT->b << endl;
}

int main()
{
	Test t1(1, 2);
	Test t2(3, 4);

	// 调用全局函数
	Test t3;
	t3 = testAdd(t1, t2);
	printT(&t3);

	// 调用成员函数
	Test t4 = t1.testAdd(t2); // 将匿名对象直接转化成t4
	t4.printT();

	Test t5;
	t5 = t1.testAdd(t2); // 将匿名对象复制给t5
	t5.printT();

	t1.testAdd2(t2); // 函数内部使用了this指针
	t1.printT();

	return 0;
}