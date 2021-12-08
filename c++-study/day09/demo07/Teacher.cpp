#include "Teacher.h"

// 构造函数
Teacher::Teacher() {
	this->m_age = 0;
	this->m_name = (char*)malloc(1);
	if (this->m_name) {
		strcpy(this->m_name, "");
	}
}

// 构造函数
Teacher::Teacher(int age, const char* name) {
	this->m_age = age;
	this->m_name = (char*)malloc(strlen(name) + 1);
	if (this->m_name) {
		strcpy(this->m_name, name);
	}
}

// 拷贝构造函数
Teacher::Teacher(const Teacher& obj) {
	// 深拷贝
	this->m_age = obj.m_age;
	this->m_name = (char*)malloc(strlen(obj.m_name) + 1);
	if (this->m_name) {
		strcpy(this->m_name, obj.m_name);
	}
}

// 析构函数
Teacher::~Teacher() {
	if (this->m_name) {
		free(this->m_name);
	}
}

// 使用类成员函数，重载运算符 "="
Teacher& Teacher::operator=(const Teacher& obj) {
	// 释放原本的内存空间
	if (this->m_name) {
		free(this->m_name);
		this->m_name = NULL;
	}
	// 深拷贝
	this->m_age = obj.m_age;
	this->m_name = (char*)malloc(strlen(obj.m_name) + 1);
	if (this->m_name) {
		strcpy(this->m_name, obj.m_name);
	}
	return *this;
}

// 使用友元函数，重载运算符 "<<"
ostream& operator<<(ostream& out, Teacher& obj) {
	cout << "age = " << obj.m_age << " name = " << obj.m_name;
	return out;
}

int Teacher::getAge() {
	return this->m_age;
}

char* Teacher::getName() {
	return this->m_name;
}

void Teacher::setAge(int age) {
	this->m_age = age;
}

void Teacher::setName(const char* name) {
	// 释放原本的内存空间
	if (this->m_name) {
		free(this->m_name);
		this->m_name = NULL;
	}
	// 深拷贝
	this->m_name = (char*)malloc(strlen(name) + 1);
	if (this->m_name) {
		strcpy(this->m_name, name);
	}
}