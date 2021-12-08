/*
 * 1. 异常处理机制
 * a) 栈解旋（unwinding）
 * b) 异常被抛出后，从进入 try 代码块起，到异常被抛掷前，这期间在栈上构造的所有对象，都会被自动析构，析构的顺序与构造的顺序相反。这一过程称为 "栈解旋（unwinding）"
*/

#include <iostream>

using namespace std;

class Test {

public:
	Test(int a, int b) {
		this->a = a;
		this->b = b;
		cout << "构造函数被调用" << endl;
	}

	~Test() {
		cout << "析构函数被调用" << endl;
	}

private:
	int a;
	int b;
};

int divide(int x, int y) {
	Test t1(3, 4), t2(5, 6);
	if (0 == y) {
		throw y;	// 抛出 int 类型的异常
	}
	return x / y;
}

int main() {
	// divide(5, 0);  如果 divide() 函数的调用写在 try 代码块之外，那么 Test 类的析构函数不会自动被调用

	try {
		int result = divide(5, 0);
		cout << "result = " << result << endl;
	}
	catch (int e) {
		cout << e << ", 被除数不能为零" << endl;
	}
	catch (...) {
		cout << "发生未知的异常";
	}
	return 0;
}