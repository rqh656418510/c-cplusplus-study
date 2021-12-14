/*
 * 1. 异常处理机制
 * a) C++ 标准输出流的简单使用
*/

#include <iostream>
#include <iomanip>

using namespace std;

void output1() {
	cout.put('h').put('e').put('l').put('l').put('o').put('\n');
}

void output2() {
	char* str = "hello world\n";
	cout.write(str, strlen(str));
}

void output3() {
	// 使用流对象的成员函数
	cout << "<Start>";
	cout.width(30);
	cout.fill('*');
	cout.setf(ios::showbase);
	cout.setf(ios::internal);
	cout << hex << 123 << "<End>\n";
}

void output4() {
	// 使用控制符
	cout << "<Start>"
		<< setw(30)
		<< setfill('*')
		<< setiosflags(ios::showbase)
		<< setiosflags(ios::internal)
		<< hex
		<< 123
		<< "<End>\n";
}

int main() {
	output1();
	output2();
	output3();
	output4();
	return 0;
}