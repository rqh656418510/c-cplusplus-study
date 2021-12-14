/**
 * 1. 重载等号运算符
 */

#include <iostream>
#include "string.h"

using namespace std;

class Name {

private:
	char* p;
	int len;

public:

	Name(const char* name) {
		cout << "有参构造函数被调用了" << endl;
		len = strlen(name);
		p = new char[len + 1];
		strcpy(p, name);
	}

	// 深拷贝的实现
	Name(const Name& name) {
		cout << "拷贝构造函数被调用了" << endl;
		len = name.getLen();
		p = new char[len + 1];
		strcpy(p, name.getP());
	}

	~Name() {
		cout << "析构函数被调用了" << endl;
		if (p != NULL) {
			delete[] p;
			p = NULL;
			len = 0;
		}
	}

	char* getP() const {
		return p;
	}

	int getLen() const {
		return len;
	}

public:
	// 使用类成员函数实现 "=" 操作符的重载
	Name& operator=(const Name& n) {
		// 释放内存空间
		if (p != NULL) {
			delete[] p;
			p = NULL;
			len = 0;
		}
		// 重新分配内存空间
		len = n.getLen();
		p = new char[len + 1];
		strcpy(p, n.getP());
		return *this;
	}
};

int main() {
	Name obj1("Peter");
	Name obj2("Tom");
	Name obj4("Tim");

	// 会自动调用拷贝构造函数（属于深拷贝）
	Name obj3 = obj1;
	cout << "obj3.name: " << obj3.getP() << ", obj3.len:  " << obj3.getLen() << endl;
	
	// 不会自动调用拷贝构造函数（属于浅拷贝）
	// 默认情况下，若这里不对 "=" 运算符进行重载，最终程序会异常终止运行（同一块内存空间被释放两次导致）
	obj4 = obj1;
	cout << "obj4.name: " << obj4.getP() << ", obj4.len:  " << obj4.getLen() << endl;
	
	return 0;
}