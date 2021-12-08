/*
 * 1. 异常处理机制
 * a) 异常的使用案例一
*/

#include <iostream>

using namespace std;

int divide(int x, int y) {
	if (0 == y) {
		throw y;	// 抛出 int 类型的异常
	}
	return x / y;
}

int main() {
	try {
		int result = divide(5, 0);
		cout << "result = " << result << endl;
	}
	catch (int e) {
		cout << e << ", 被除数不能为零" << endl;
	}
	// 会捕获所有未被捕获的异常，必须最后出现
	catch (...) {
		throw "发生未知的异常 ...";
	}

	cout << "程序正常结束运行" << endl;
	return 0;
}