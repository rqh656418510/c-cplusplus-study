/**
 * 面向对象设计案例 - 点和圆的关系
 */

#include <iostream>

using namespace std;

class Point {

public:
    Point() {

    }

    Point(double x, double y) {
        this->m_X = x;
        this->m_Y = y;
    }

    double getX() const {
        return m_X;
    }

    void setX(double mX) {
        m_X = mX;
    }

    double getY() const {
        return m_Y;
    }

    void setY(double mY) {
        m_Y = mY;
    }

private:
    double m_X;
    double m_Y;

};

class Circle {

public:

    Circle() {

    }

    Circle(double r, const Point &c) {
        this->m_R = r;
        this->m_Center = c;
    }

    double getR() const {
        return this->m_R;
    }

    void setR(double r) {
        this->m_R = r;
    }

    const Point &getCenter() const {
        return this->m_Center;
    }

    void setCenter(const Point &p) {
        this->m_Center = p;
    }

    // 利用成员函数，判断点和圆的关系
    void isInCircle(const Point &p) {
        double rDistance = this->m_R * this->m_R;
        double distance = (this->m_Center.getX() - p.getX()) * (this->m_Center.getX() - p.getX()) + (this->m_Center.getY() - p.getY()) * (this->m_Center.getY() - p.getY());
        if (rDistance > distance) {
            cout << "点在圆内" << endl;
        } else if (rDistance == distance) {
            cout << "点在圆上" << endl;
        } else {
            cout << "点在圆外" << endl;
        }
    }

private:
    double m_R;          // 半径
    Point m_Center;      // 圆心

};

// 利用全局函数，判断点和圆的关系
void isInCircle(const Circle &c, const Point &p) {
    double rDistance = c.getR() * c.getR();
    double distance = (c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) + (c.getCenter().getY() - p.getY()) * (c.getCenter().getY() - p.getY());
    if (rDistance > distance) {
        cout << "点在圆内" << endl;
    } else if (rDistance == distance) {
        cout << "点在圆上" << endl;
    } else {
        cout << "点在圆外" << endl;
    }
}

void test01() {
    Point p(11, 10);

    Point center(10, 0);
    Circle c(10, center);

    isInCircle(c, p);
}

void test02() {
    Point p(10, 10);

    Point center(10, 0);
    Circle c(10, center);

    c.isInCircle(p);
}

int main() {
    test01();
    test02();
    return 0;
}
