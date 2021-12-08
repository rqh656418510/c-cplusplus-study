#pragma once

#include <iostream>

using namespace std;

template <class T>

class MyVector {

public:
	MyVector(int size = 0);
	~MyVector();
	MyVector(const MyVector& obj);

public:
	int getSize();

public:
	T& operator[](int index);
	MyVector& operator=(const MyVector& obj);
	friend ostream& operator<< <T>(ostream& out, MyVector& obj);

private:
	T* m_space; // ָ�������ָ��
	int m_size;
};