#include "Array.h"

Array::Array(int length) {
	cout << "有参构造函数被调用" << endl;
	if (length < 0) {
		length = 0;
	}
	this->m_length = length;
	this->m_space = new int[length];
}

Array::Array(const Array& array) {
	cout << "拷贝构造函数被调用" << endl;
	// 深拷贝，单独分配内存空间
	this->m_length = array.m_length;
	this->m_space = new int[array.m_length];
	for (int i = 0; i < array.m_length; i++) {
		this->m_space[i] = array.m_space[i];
	}
}

Array::~Array() {
	cout << "析构函数被调用" << endl;
	if (this->m_space != NULL) {
		delete[] this->m_space;
		this->m_space = NULL;
		this->m_length = 0;
	}
}

// 使用类成员函数重载 "[]" 数组下标运算符，用于数组元素的赋值和取值
int& Array::operator[](int index) {
	return this->m_space[index];
}

// 使用类成员函数重载 "=" 运算符，用于数组之间的赋值
Array& Array::operator=(const Array& array) {
	if (this->m_space != NULL) {
		delete[] this->m_space;
		this->m_space = NULL;
		this->m_length = 0;
	}
	// 深拷贝，单独分配内存空间
	this->m_length = array.m_length;
	this->m_space = new int[array.m_length];
	for (int i = 0; i < array.m_length; i++) {
		this->m_space[i] = array.m_space[i];
	}
	return *this;
}

// 使用类成员函数重载 "==" 运算符，判断两个数组是否相同
bool Array::operator==(const Array& array) {
	if (this->m_length != array.m_length) {
		return false;
	}
	for (int i = 0; i < this->m_length; i++) {
		if (this->m_space[i] != array.m_space[i]) {
			return false;
		}
	}
	return true;
}

// 使用类成员函数重载 "!=" 运算符，判断两个数组是否不相同
bool Array::operator!=(const Array& array) {
	return !(*this == array);
}

int Array::length() {
	return this->m_length;
}