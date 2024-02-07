/*
 * 1. 异常处理机制
 * a) C++ 标准输入流的简单使用
*/

#include <iostream>

using namespace std;

void input1() {
	int number;
	cout << "请输入一个数字: ";
	cin >> number;
	cout << "输入的数字是: " << number << endl;
}

void input2() {
	char buf[1024];
	cout << "请输入字符串: ";
	cin >> buf;		// 当遇到空格符时，会停止接收数据输入
	cout << "输入的字符串: ";
	cout << buf << endl;
}

void input3() {
	char ch;
	cout << "请输入字符串: ";
	while ((ch = cin.get()) != EOF)		// 如果缓冲区没有数据，则程序会阻塞
	{
		cout << ch << " ";
	}
}

void input4() {
	char a, b, c;
	cout << "请输入字符串: ";
	cin.get(a);		// 如果缓冲区没有数据，则程序会阻塞
	cin.get(b);
	cin.get(c);
	cout << a << b << c;
}

void input5() {
	char buf[256];
	cout << "请输入字符串: ";
	cin.getline(buf, 256);		// 当遇到空格符时，不会停止接收数据输入
	cout << buf << endl;
}

void input6() {
	char buf1[256];
	char buf2[256];
	cout << "请输入字符串:";  // 例如输入：abc  efghi
	cin >> buf1;
	cin.ignore(2);		// 忽略缓冲区的数据
	cin.getline(buf2, 256);
	cout << buf1 << endl;
	cout << buf2 << endl;
}

void input7() {
	char buf1[256];
	char buf2[256];
	cout << "请输入字符串:";  // 例如输入：abc  efghi
	cin >> buf1;
	cin.ignore(2);
	int num = cin.peek();	// 查看缓冲区是否有数据
	cout << num << endl;
	cin.getline(buf2, 256);
	cout << buf1 << endl;
	cout << buf2 << endl;
}

void input8() {
	// 分开处理输入的整数和字符
	cout << "Please, enter a number or a word: ";
	char c = std::cin.get();

	if ((c >= '0') && (c <= '9'))
	{
		int n;
		cin.putback(c);		// 将数据放回缓冲区
		cin >> n;
		cout << "You entered a number: " << n << '\n';
	}
	else
	{
		char ch;
		cin.putback(c);		// 将数据放回缓冲区
		cin.get(ch);
		cout << "You entered a character: " << ch << '\n';
	}
}

int main() {
	input8();
	return 0;
}