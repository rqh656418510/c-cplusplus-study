/**
 * 1. 作业案例-设计圆类
 */

#include <iostream>

using namespace std;

class Circle {

public:

    Circle() {

    }

    Circle(double _radius) : radius(_radius) {

    }

    void setRadius(double radius) {
        this->radius = radius;
    }

    double getRadius() {
        return this->radius;
    }

    double getArea() {
        if (this->radius == 0) {
            return 0;
        }
        this->area = 3.14 * this->radius * this->radius;
        return this->area;
    }

private:

    double radius = 0;  // 圆形的半径
    double area = 0;    // 圆形的面积

};

int main() {
    Circle c1(3);
    cout << "radius = " << c1.getRadius() << " , area = " << c1.getArea() << endl;

    Circle c2;
    c2.setRadius(6);
    cout << "radius = " << c2.getRadius() << " , area = " << c2.getArea() << endl;

    return 0;
}
