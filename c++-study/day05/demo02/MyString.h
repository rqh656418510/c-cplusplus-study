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
	// ʹ�����Ա�������� "[]" �����
	char& operator[](int index);

	// ʹ�����Ա�������� "=" �����
	MyString& operator=(const char* p);
	MyString& operator=(const MyString& str);

	// ʹ�����Ա�������� "==" �����
	bool operator==(const char* p) const;
	bool operator==(const MyString str) const;

	// ʹ�����Ա�������� "!=" �����
	bool operator!=(const char* p) const;
	bool operator!=(const MyString str) const;

	// ʹ�����Ա�������� ">" �����
	bool operator>(const char* p) const;
	bool operator>(const MyString str) const;

	// ʹ�����Ա�������� "<" �����
	bool operator<(const char* p) const;
	bool operator<(const MyString str) const;

	// ʹ����Ԫ�������� "<<" �����
	friend ostream& operator<<(ostream& out, MyString& str);

	// ʹ����Ԫ�������� ">>" �����
	friend iostream& operator>>(iostream& in, MyString& str);

public:
	int length();
	char* c_str();

private:
	int m_length;
	char* m_space;
};