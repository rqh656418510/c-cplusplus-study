/**
 * 1. 验证在父类的构造函数中能调用虚函数，是否可以实现多态
 * a) 分析：子类的 VPTR 指针是分步完成初始化的，当执行父类的构造函数时，子类 的 VPTR 指针指向父类的虚函数表，当父类的构造函数执行完毕后，才会把子类的 VPTR 指针指向子类的虚函数表
 * b) 结论：在父类的构造函数中调用虚函数，不能实现多态
 */

#include <iostream>

using namespace std;

class Parent {

public:
	Parent(int a) {
		this->a = a;
		// 在父类的构造函数中调用虚函数
		print();
	}

	virtual void print() {
		cout << "I'm parent, a = " << a << endl;
	}

private:
	int a;
};

class Child : public Parent {
public:

	Child(int a, int c) : Parent(a) {
		this->c = c;
	}

	virtual void print() {
		cout << "I'm child, c = " << c << endl;
	}

private:
	int c;
};

int main() {
	Child child(5, 8);
	return 0;
}
