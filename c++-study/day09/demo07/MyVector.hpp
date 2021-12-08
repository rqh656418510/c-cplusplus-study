#include "MyVector.h"

// ���캯��
template <typename T>
MyVector<T>::MyVector(int size) {
	this->m_size = size;
	// �����ڴ�ռ�
	this->m_space = new T[size];
}

// ��������
template <typename T>
MyVector<T>::~MyVector() {
	if (this->m_space) {
		// �ͷ��ڴ�ռ�
		delete[] this->m_space;
		this->m_size = 0;
		this->m_space = NULL;
	}
}

// �������캯��
template <typename T>
MyVector<T>::MyVector(const MyVector<T>& obj) {
	// ���
	this->m_size = obj.m_size;
	this->m_space = new T[obj.m_size];
	for (int i = 0; i < obj.m_size; i++) {
		this->m_space[i] = obj.m_space[i];
	}
}

// ��ͨ���Ա����
template <typename T>
int MyVector<T>::getSize() {
	return this->m_size;
}

// ʹ�����Ա��������������� "[]"
template <typename T>
T& MyVector<T>::operator[](int index) {
	return this->m_space[index];
}

// ʹ�����Ա��������������� "="
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& obj) {
	if (this->m_space) {
		// �ͷ�ԭ�����ڴ�ռ�
		delete[] this->m_space;
		this->m_size = 0;
		this->m_space = NULL;
	}
	// ���
	this->m_size = obj.m_size;
	this->m_space = new T[obj.m_size];
	for (int i = 0; i < obj.m_size; i++) {
		this->m_space[i] = obj.m_space[i];
	}
	return *this;
};

// ʹ����Ԫ��������������� "<<"
template <typename T>
ostream& operator<<(ostream& out, MyVector<T>& obj) {
	for (int i = 0; i < obj.m_size; i++) {
		cout << obj.m_space[i] << ", ";
	}
	return out;
}