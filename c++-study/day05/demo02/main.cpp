/**
 * 1. 自定义 MyString 类，并实现各种操作符的重载
 */

#include "MyString.h"

int main() {

	// 自动调用有参构造函数
	MyString str1("Tom");
	MyString str2(NULL);
	MyString str3("Peter");

	// 自动调用拷贝构造函数
	MyString str4 = str1;

	// 重载 "<<" 运算符
	cout << "str2 = " << str2 << endl;
	cout << "str4 = " << str4 << endl;
	cout << endl;

	// 重载 "=" 运算符，属于深拷贝
	str4 = str3;
	cout << "str4 = " << str4 << endl;
	str4 = "Jim";
	cout << "str4 = " << str4 << endl;
	str4 = NULL;
	cout << "str4 = " << str4 << endl;
	cout << endl;

	// 重载 "[]" 运算符
	MyString str5("David");
	str5[0] = 'F';
	cout << "str5[0] = " << str5[0] << endl;
	cout << "str5 = " << str5 << endl;
	cout << endl;

	// 重载 "==" 运算符
	MyString str6("Aaron");
	MyString str7 = str6;
	cout << str6 << (str6 == str7 ? " = " : " != ") << str7 << endl;

	// 重载 "!=" 运算符
	cout << str6 << (str6 != NULL ? " != " : " = ") << " NULL" << endl;
	cout << endl;

	// 重载 "<" 运算符
	MyString str8("AAAA");
	MyString str9("BBBB");
	cout << str8 << (str8 < str9 ? " < " : " > ") << str9 << endl;
	cout << str8 << (str8 < "CCCC" ? " < " : " > ") << "CCCC" << endl;

	// 重载 ">" 运算符
	cout << str9 << (str9 > str8 ? " > " : " < ") << str8 << endl;
	cout << str9 << (str9 > "DDDD" ? " > " : " < ") << "DDDD" << endl;
	cout << endl;

	// 重载 ">>" 运算符
	MyString str11(5);
	cout << "请输入长度为 5 的字符串：" << endl;
	cin >> str11.c_str();
	cout << "str11 = " << str11 << endl;

	// MyString str4 = NULL;   此写法，会自动调用有参构造函数 `MyString(const char* p);`

	// MyString str1("AB");
	// MyString str2 = str1;
	// str2 = NULL:    此写法，会自动调用 "=" 运算符重载的函数 `bool operator==(const char* p) const;`

	return 0;
}