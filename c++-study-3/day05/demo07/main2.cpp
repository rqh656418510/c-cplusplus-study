/**
 * 理解抽象类
 */

#include <iostream>

using namespace std;

// 抽象类
class Figure {

public:
    // 声明纯虚函数，计算面积
    virtual double getArea() = 0;
};

class Circle : public Figure {

public:

    Circle(double r) {
        this->r = r;
    }

    // 实现纯虚函数，计算圆的面积
    virtual double getArea() {
        double area = 3.14 * r * r;
        cout << "圆的面积: " << area << endl;
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

    // 实现纯虚函数，计算三角形的面积
    virtual double getArea() {
        double area = a * b / 2;
        cout << "三角形的面积: " << area << endl;
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

    // 实现纯虚函数，计算四边形的面积
    virtual double getArea() {
        double area = a * b;
        cout << "四边形的面积: " << area << endl;
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
    // Figure f;    // 错误写法，抽象类不能实例化

    Triangle Triangle(20, 30);
    Square square(50, 60);

    // 可以声明抽象类的指针
    Figure* pBase = new Circle(5.3);
    pBase->getArea();

    // 可以声明抽象类的引用
    Figure& base = square;
    base.getArea();

    printArea(&Triangle);

    return 0;
}
