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
	// 使用类成员函数重载 "[]" 数组下标运算符，用于数组元素的赋值和取值
	int& operator[](int index);

	// 使用类成员函数重载 "=" 运算符，用于数组之间的赋值
	Array& operator=(const Array& array);

	// 使用类成员函数重载 "==" 运算符，判断两个数组是否相同
	bool operator==(const Array & array);

	// 使用类成员函数重载 "!=" 运算符，判断两个数组是否不相同
	bool operator!=(const Array& array);

private:
	int m_length;
	int* m_space;
};
