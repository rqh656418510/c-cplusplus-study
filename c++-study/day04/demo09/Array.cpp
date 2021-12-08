#include "Array.h"

Array::Array(int length) {
	cout << "�вι��캯��������" << endl;
	if (length < 0) {
		length = 0;
	}
	this->m_length = length;
	this->m_space = new int[length];
}

Array::Array(const Array& array) {
	cout << "�������캯��������" << endl;
	// ��������������ڴ�ռ�
	this->m_length = array.m_length;
	this->m_space = new int[array.m_length];
	for (int i = 0; i < array.m_length; i++) {
		this->m_space[i] = array.m_space[i];
	}
}

Array::~Array() {
	cout << "��������������" << endl;
	if (this->m_space != NULL) {
		delete[] this->m_space;
		this->m_space = NULL;
		this->m_length = 0;
	}
}

// ʹ�����Ա�������� "[]" �����±����������������Ԫ�صĸ�ֵ��ȡֵ
int& Array::operator[](int index) {
	return this->m_space[index];
}

// ʹ�����Ա�������� "=" ���������������֮��ĸ�ֵ
Array& Array::operator=(const Array& array) {
	if (this->m_space != NULL) {
		delete[] this->m_space;
		this->m_space = NULL;
		this->m_length = 0;
	}
	// ��������������ڴ�ռ�
	this->m_length = array.m_length;
	this->m_space = new int[array.m_length];
	for (int i = 0; i < array.m_length; i++) {
		this->m_space[i] = array.m_space[i];
	}
	return *this;
}

// ʹ�����Ա�������� "==" ��������ж����������Ƿ���ͬ
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

// ʹ�����Ա�������� "!=" ��������ж����������Ƿ���ͬ
bool Array::operator!=(const Array& array) {
	return !(*this == array);
}

int Array::length() {
	return this->m_length;
}