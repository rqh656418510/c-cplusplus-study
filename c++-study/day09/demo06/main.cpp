/*
 * 1. ��ģ���е� static �ؼ���
*/

#include <iostream>

using namespace std;

const double pi = 3.14;

template <typename T> class Circle {

public:
	Circle(T radius = 0) {
		this->m_radius = radius;
		this->m_total++;
	}

	void setRadius(T radius) {
		this->m_radius = radius;
	}

	T getRadius() {
		return this->m_radius;
	}

	double getGirth() {
		return 2 * pi * this->m_radius;
	}

	double getArea() {
		return pi * this->m_radius * this->m_radius;
	}

	// ��ģ��ľ�̬��Ա����
	static int getTotal() {
		return m_total;
	}

private:
	T m_radius;

	// ��ģ��ľ�̬���ݳ�Ա
	static int m_total;

};

// ��ʼ����ģ��ľ�̬���ݳ�Ա
template <typename T> int Circle<T>::m_total = 0;

int main() {
	// ÿ���������͵�ģ���඼���Լ�����һ�ݵ���ģ��� static ���ݳ�Ա����

	Circle<int> c1(4), c2(6);
	cout << "m_total = " << Circle<int>::getTotal() << endl;
	cout << "radius = " << c1.getRadius() << ", girth = " << c1.getGirth() << ", area = " << c1.getArea() << endl;
	cout << "radius = " << c2.getRadius() << ", girth = " << c2.getGirth() << ", area = " << c2.getArea() << endl;

	Circle<float> c3(3.2), c4(4.3), c5(6.2);
	cout << "m_total = " << Circle<float>::getTotal() << endl;
	cout << "radius = " << c3.getRadius() << ", girth = " << c3.getGirth() << ", area = " << c3.getArea() << endl;
	cout << "radius = " << c4.getRadius() << ", girth = " << c4.getGirth() << ", area = " << c4.getArea() << endl;
	cout << "radius = " << c5.getRadius() << ", girth = " << c5.getGirth() << ", area = " << c5.getArea() << endl;

	return 0;
}