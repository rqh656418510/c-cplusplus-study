#pragma once

#include <iostream>

using namespace std;

class Array {
public:
	Array(int length);

	Array(const Array& array);

	~Array();

public:
	int length();

public:
	// ʹ�����Ա�������� "[]" �����±����������������Ԫ�صĸ�ֵ��ȡֵ
	int& operator[](int index);

	// ʹ�����Ա�������� "=" ���������������֮��ĸ�ֵ
	Array& operator=(const Array& array);

	// ʹ�����Ա�������� "==" ��������ж����������Ƿ���ͬ
	bool operator==(const Array & array);

	// ʹ�����Ա�������� "!=" ��������ж����������Ƿ���ͬ
	bool operator!=(const Array& array);

private:
	int m_length;
	int* m_space;
};
