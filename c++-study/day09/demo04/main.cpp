/*
 * 1. 类模板的使用
 * a) 单个类模板的使用
 * b) 类模板做函数参数
*/

#include <iostream>

using namespace std;

// 模板声明
template <typename T>

// 类定义
class A {

public:

	A(T t) {
		this->t = t;
	}

	T& getT() {
		return this->t;
	}

private:
	T t;

};

// 类模板做函数参数
void printA(A<int>& a) {
	cout << a.getT() << endl;
}

int main() {
	A<int> a(100);	// 模板类是抽象的，需要声明具体的类型（模板参数列表），这里的 <int> 不能省略
	cout << a.getT() << endl;

	A<int> a2(50);
	printA(a2);

	return 0;
}