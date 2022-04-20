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

void Array::setData(int index, int value) {
	this->m_space[index] = value;
}

int Array::getData(int index) {
	return this->m_space[index];
}

int Array::length() {
	return this->m_length;
}