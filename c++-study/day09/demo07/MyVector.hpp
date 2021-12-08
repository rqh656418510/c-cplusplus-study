#include "MyVector.h"

// 构造函数
template <typename T>
MyVector<T>::MyVector(int size) {
	this->m_size = size;
	// 分配内存空间
	this->m_space = new T[size];
}

// 析构函数
template <typename T>
MyVector<T>::~MyVector() {
	if (this->m_space) {
		// 释放内存空间
		delete[] this->m_space;
		this->m_size = 0;
		this->m_space = NULL;
	}
}

// 拷贝构造函数
template <typename T>
MyVector<T>::MyVector(const MyVector<T>& obj) {
	// 深拷贝
	this->m_size = obj.m_size;
	this->m_space = new T[obj.m_size];
	for (int i = 0; i < obj.m_size; i++) {
		this->m_space[i] = obj.m_space[i];
	}
}

// 普通类成员函数
template <typename T>
int MyVector<T>::getSize() {
	return this->m_size;
}

// 使用类成员函数，重载运算符 "[]"
template <typename T>
T& MyVector<T>::operator[](int index) {
	return this->m_space[index];
}

// 使用类成员函数，重载运算符 "="
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& obj) {
	if (this->m_space) {
		// 释放原本的内存空间
		delete[] this->m_space;
		this->m_size = 0;
		this->m_space = NULL;
	}
	// 深拷贝
	this->m_size = obj.m_size;
	this->m_space = new T[obj.m_size];
	for (int i = 0; i < obj.m_size; i++) {
		this->m_space[i] = obj.m_space[i];
	}
	return *this;
};

// 使用友元函数，重载运算符 "<<"
template <typename T>
ostream& operator<<(ostream& out, MyVector<T>& obj) {
	for (int i = 0; i < obj.m_size; i++) {
		cout << obj.m_space[i] << ", ";
	}
	return out;
}