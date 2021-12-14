/**
 * 1. 友元函数的使用
 */

#include <iostream>

using namespace std;

class A {
public:
	A(int a) {
		this->a = a;
	}

	int getA() {
		return this->a;
	}

	// 声明友元函数
	friend void update2(A* p);

private:
	int a;
};

void update1(A* p) {
	// p->a = 30;  // 错误写法，在普通函数（全局函数）内，私有数据成员不能在类外被访问
}

void update2(A* p) {
	p->a = 30;		// 在友元函数内，可以通过对象参数访问私有数据成员
}

int main() {
	A* a = new A(10);
	update2(a);		// 调用友元函数
	cout << "a = " << a->getA() << endl;
	delete a;
	return 0;
}