/*
 * 1. 类模板的实战案例（编写数组模板类）
*/

#include "Teacher.cpp"
#include "MyVector.hpp"

int main() {

	// 自动调用构造函数
	MyVector<int> v(5);

	// 重载运算符 "[]"
	for (int i = 0; i < v.getSize(); i++) {
		v[i] = i + 1;
	}

	// 重载运算符 "<<"
	cout << v << endl;

	// 自动调用拷贝构造函数
	MyVector<int> v2 = v;
	cout << v2 << endl;

	// 重载运算符 "="
	MyVector<int> v3(2);
	v3 = v2;
	cout << v3 << endl;

	// 容器存放类对象
	MyVector<Teacher> teachers(3);
	for (int i = 0; i < teachers.getSize(); i++) {
		Teacher t(i + 20, "Jim");
		teachers[i] = t;
	}
	cout << teachers << endl;

	// 容器存放指针
	MyVector<Teacher*> points(4);
	for (int i = 0; i < points.getSize(); i++) {
		points[i] = new Teacher(25 + i, "Tom");
	}
	for (int i = 0; i < points.getSize(); i++) {
		Teacher* obj = points[i];
		cout << "age = " << obj->getAge() << " name = " << obj->getName() << ", ";
	}

	return 0;
}