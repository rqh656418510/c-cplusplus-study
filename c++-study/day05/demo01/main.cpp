/**
 * 1. 重载函数运算符 "()"
 */

#include <iostream>

using namespace std;

class Test {
public:
	int operator()(int a, int b) {
		return a + b;
	}
};

int main() {
	Test test;
	cout << test(3, 4) << endl;
	return 0;
}