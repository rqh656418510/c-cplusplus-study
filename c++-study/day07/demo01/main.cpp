/**
 * 1. 证明虚函数表指针 VPTR 的存在
 */

#include <iostream>

using namespace std;

class Parent1 {
public:
	Parent1(int a) {
		this->a = a;
	}

	// 不声明虚函数
	void print() {
		cout << "I'm parent1" << endl;
	}

private:
	int a;
};

class Parent2 {
public:
	Parent2(int a) {
		this->a = a;
	}

	// 声明虚函数
	virtual void print() {
		cout << "I'm parent2" << endl;
	}

private:
	int a;
};

int main() {
	// 由于指针也是一种数据类型，由于在Parent2类中声明了虚函数，若Parent2类里存在VPTR指针，那么下面两个类的大小应该是不一样的
	cout << "sizeof(Parent1): " << sizeof(Parent1) << endl;
	cout << "sizeof(Parent2): " << sizeof(Parent2) << endl;
	return 0;
}