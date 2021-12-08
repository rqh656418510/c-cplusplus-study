/*
 * 1. ��ģ���ʵս��������д����ģ���ࣩ
*/

#include "Teacher.cpp"
#include "MyVector.hpp"

int main() {

	// �Զ����ù��캯��
	MyVector<int> v(5);

	// ��������� "[]"
	for (int i = 0; i < v.getSize(); i++) {
		v[i] = i + 1;
	}

	// ��������� "<<"
	cout << v << endl;

	// �Զ����ÿ������캯��
	MyVector<int> v2 = v;
	cout << v2 << endl;

	// ��������� "="
	MyVector<int> v3(2);
	v3 = v2;
	cout << v3 << endl;

	// ������������
	MyVector<Teacher> teachers(3);
	for (int i = 0; i < teachers.getSize(); i++) {
		Teacher t(i + 20, "Jim");
		teachers[i] = t;
	}
	cout << teachers << endl;

	// �������ָ��
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