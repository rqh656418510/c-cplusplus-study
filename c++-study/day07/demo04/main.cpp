/**
 * 1. ���麯���������Ļ����﷨
 * a) ����һ��ͼ�γ����� Figure���������˸������ͼ������Ĵ��麯�� getArea()��Ȼ���ٶ��� Circle��Triangle��Squre �����࣬������ʵ���˴��麯�� getArea() �����㲻ͬͼ�ε����
 */

#include <iostream>

using namespace std;

// ������
class Figure {

public:
	// �������麯�����������
	virtual double getArea() = 0;
};

class Circle : public Figure {

public:

	Circle(double r) {
		this->r = r;
	}

	// ����Բ�����
	virtual double getArea() {
		double area = 3.14 * r * r;
		cout << "Բ�����: " << area << endl;
		return area;
	}

private:
	double r;
};

class Triangle : public Figure {

public:
	Triangle(double a, double b) {
		this->a = a;
		this->b = b;
	}

	// ���������ε����
	virtual double getArea() {
		double area = a * b / 2;
		cout << "�����ε����: " << area << endl;
		return area;
	}

private:
	double a;
	double b;
};

class Square : public Figure {

public:
	Square(double a, double b) {
		this->a = a;
		this->b = b;
	}

	// �����ı��ε����
	virtual double getArea() {
		double area = a * b;
		cout << "�ı��ε����: " << area << endl;
		return area;
	}

private:
	double a;
	double b;
};

void printArea(Figure* base) {
	base->getArea();
}

int main() {
	// Figure f;		// ����д���������಻��ʵ����

	Triangle Triangle(20, 30);
	Circle circle(6.8);
	Square square(50, 60);

	// ���������������ָ��
	Figure* pBase = new Circle(5.3);
	pBase->getArea();

	// �������������������
	Figure& base = square;
	base.getArea();

	printArea(&Triangle);

	return 0;
}