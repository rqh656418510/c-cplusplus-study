#include "MyString.h"

// 无参构造函数
MyString::MyString() {
	// 初始化为空字符串
	this->m_length = 0;
	this->m_space = new char[this->m_length + 1];
	strcpy(this->m_space, "");
}

// 有参构造函数
MyString::MyString(int len) {
	if (len < 0) {
		len = 0;
	}
	// 初始化为空字符串
	this->m_length = len;
	this->m_space = new char[this->m_length + 1];
	strcpy(this->m_space, "");
}

// 有参构造函数
MyString::MyString(const char* p) {
	if (p == NULL) {
		// 初始化为空字符串
		this->m_length = 0;
		this->m_space = new char[this->m_length + 1];
		strcpy(this->m_space, "");
	}
	else {
		this->m_length = strlen(p);
		this->m_space = new char[this->m_length + 1];
		strcpy(this->m_space, p);
	}
}

// 拷贝构造函数
MyString::MyString(const MyString& str) {
	// 深拷贝，重新分配内存空间
	this->m_length = str.m_length;
	this->m_space = new char[this->m_length + 1];
	strcpy(this->m_space, str.m_space);
}

// 析构函数
MyString::~MyString() {
	// 释放内存空间
	if (this->m_space != NULL) {
		delete[] this->m_space;
		this->m_space = NULL;
		this->m_length = 0;
	}
}

// 使用类成员函数重载 "[]" 运算符
char& MyString::operator[](int index) {
	return this->m_space[index];
}

// 使用类成员函数重载 "=" 运算符
MyString& MyString::operator=(const char* p) {
	// 释放内存空间
	if (this->m_space != NULL) {
		delete[] this->m_space;
		this->m_space = NULL;
		this->m_length = 0;
	}
	// 深拷贝，重新分配内存空间
	if (p == NULL) {
		// 初始化为空字符串
		this->m_length = 0;
		this->m_space = new char[this->m_length + 1];
		strcpy(this->m_space, "");
	}
	else {
		this->m_length = strlen(p);
		this->m_space = new char[this->m_length + 1];
		strcpy(this->m_space, p);
	}
	return *this;
}

// 使用类成员函数重载 "=" 运算符
MyString& MyString::operator=(const MyString& str) {
	// 释放内存空间
	if (this->m_space != NULL) {
		delete[] this->m_space;
		this->m_space = NULL;
		this->m_length = 0;
	}
	// 深拷贝，重新分配内存空间
	this->m_length = str.m_length;
	this->m_space = new char[this->m_length + 1];
	strcpy(this->m_space, str.m_space);
	return *this;
}

// 使用类成员函数重载 "==" 运算符
bool MyString::operator==(const char* p) const {
	if (p == NULL) {
		if (this->m_length == 0) {
			return true;
		}
		return false;
	}
	if (this->m_length != strlen(p)) {
		return false;
	}
	return !strcmp(this->m_space, p);
}

bool MyString::operator==(const MyString str) const {
	if (this->m_length != str.m_length) {
		return false;
	}
	return !strcmp(this->m_space, str.m_space);
}

// 使用类成员函数重载 "!=" 运算符
bool MyString::operator!=(const char* p) const {
	return !(*this == p);
}

bool MyString::operator!=(const MyString str) const {
	return !(*this == str);
}

// 使用类成员函数重载 ">" 运算符
bool MyString::operator>(const char* p) const {
	return strcmp(p, this->m_space) < 0;
}

bool MyString::operator>(const MyString str) const {
	return strcmp(str.m_space, this->m_space) < 0;
}

// 使用类成员函数重载 "<" 运算符
bool MyString::operator<(const char* p) const {
	return strcmp(this->m_space, p) < 0;
}

bool MyString::operator<(const MyString str) const {
	return strcmp(this->m_space, str.m_space) < 0;
}

// 使用友元函数重载 "<<" 运算符
ostream& operator<<(ostream& out, MyString& str) {
	out << str.m_space;
	return out;
}

// 使用友元函数重载 ">>" 运算符
iostream& operator>>(iostream& in, MyString& str)
{
	in >> str.m_space;
	return in;
}

int MyString::length()
{
	return this->m_length;
}

char* MyString::c_str() {
	return this->m_space;
}