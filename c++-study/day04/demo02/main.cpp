/**
 * 1. 强化训练使用数组类、类的封装
 */

#include <iostream>
#include "Array.h"

using namespace std;

int main() {

	// 自动调用构造函数初始化数组
	Array array1(5);

	// 数组赋值
	for (int i = 0; i < array1.length(); i++) {
		array1.setData(i, i);
	}

	// 打印数组
	for (int i = 0; i < array1.length(); i++) {
		cout << "array1[" << i << "] = " << array1.getData(i) << endl;
	}

	// 自动调用拷贝构造函数初始化数组
	Array array2 = array1;

	// 打印数组
	for (int i = 0; i < array2.length(); i++) {
		cout << "array2[" << i << "] = " << array2.getData(i) << endl;
	}

	return 0;
}