/*
 * 1. �쳣�������
 * a) C++ ��׼������ļ�ʹ��
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
	// ʹ��������ĳ�Ա����
	cout << "<Start>";
	cout.width(30);
	cout.fill('*');
	cout.setf(ios::showbase);
	cout.setf(ios::internal);
	cout << hex << 123 << "<End>\n";
}

void output4() {
	// ʹ�ÿ��Ʒ�
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