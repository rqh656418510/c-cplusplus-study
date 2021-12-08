/**
 * 1. 自定义数组类 `Array`，并使用类成员函数分别对 `Array` 类的 `[]`、`=`、`==`、`!=` 运算符进行重载
 */

#include <iostream>
#include "Array.h"

using namespace std;

int main() {

	// 自动调用构造函数
	Array array1(5);

	for (int i = 0; i < array1.length(); i++) {
		array1[i] = i;
	}

	for (int i = 0; i < array1.length(); i++) {
		cout << "array1[" << i << "] = " << array1[i] << endl;
	}

	// 自动调用拷贝构造函数（属于深拷贝）
	Array array2 = array1;

	for (int i = 0; i < array2.length(); i++) {
		cout << "array2[" << i << "] = " << array2[i] << endl;
	}

	// 自动调用拷贝构造函数（属于深拷贝）
	Array array3 = array1;

	// 不会自动调用拷贝构造函数（属于浅拷贝）
	// 默认情况下，若这里不对 "=" 运算符进行重载，最终程序会异常终止运行（由于同一块内存空间被释放两次导致）
	array3 = array2;
	for (int i = 0; i < array3.length(); i++) {
		cout << "array3[" << i << "] = " << array3[i] << endl;
	}

	// 判断两个数组是否相同
	bool result1 = array1 == array2;
	string strResult1 = result1 ? "=" : "!=";
	cout << "array1 " << strResult1 << " array2 " << endl;

	// 判断两个数组是否不相同
	bool result2 = array1 != array2;
	string strResult2 = result2 ? "!=" : "=";
	cout << "array1 " << strResult2 << " array2 " << endl;

	return 0;
}