#include <iostream>
#include "point.h"

using namespace std;

Point::Point() {

}

Point::Point(double x, double y) {
    this->m_X = x;
    this->m_Y = y;
}

double Point::getX() const {
    return this->m_X;
}

void Point::setX(double x) {
    this->m_X = x;
}

double Point::getY() const {
    return this->m_Y;
}

void Point::setY(double y) {
    this->m_Y = y;
}