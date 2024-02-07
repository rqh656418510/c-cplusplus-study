#pragma once

#include <iostream>
#include "string.h"

using namespace std;

class MyString {

public:
	MyString();
	MyString(int len);
	MyString(const char* p);
	MyString(const MyString& str);

public:
	~MyString();

public:
	// 使用类成员函数重载 "[]" 运算符
	char& operator[](int index);

	// 使用类成员函数重载 "=" 运算符
	MyString& operator=(const char* p);
	MyString& operator=(const MyString& str);

	// 使用类成员函数重载 "==" 运算符
	bool operator==(const char* p) const;
	bool operator==(const MyString str) const;

	// 使用类成员函数重载 "!=" 运算符
	bool operator!=(const char* p) const;
	bool operator!=(const MyString str) const;

	// 使用类成员函数重载 ">" 运算符
	bool operator>(const char* p) const;
	bool operator>(const MyString str) const;

	// 使用类成员函数重载 "<" 运算符
	bool operator<(const char* p) const;
	bool operator<(const MyString str) const;

	// 使用友元函数重载 "<<" 运算符
	friend ostream& operator<<(ostream& out, MyString& str);

	// 使用友元函数重载 ">>" 运算符
	friend iostream& operator>>(iostream& in, MyString& str);

public:
	int length();
	char* c_str();

private:
	int m_length;
	char* m_space;
};