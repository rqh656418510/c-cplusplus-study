#include <iostream>
#include "circle.h"

using namespace std;

Circle::Circle() {

}

Circle::Circle(double r, const Point &c) {
    this->m_R = r;
    this->m_Center = c;
}

double Circle::getR() const {
    return this->m_R;
}

void Circle::setR(double r) {
    this->m_R = r;
}

const Point &Circle::getCenter() const {
    return this->m_Center;
}

void Circle::setCenter(const Point &p) {
    this->m_Center = p;
}

void Circle::isInCircle(const Point &p) const {
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
