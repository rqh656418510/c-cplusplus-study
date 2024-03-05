#pragma once

#include "point.h"

class Circle {

// 圆
public:

    Circle();

    Circle(double r, const Point &c);

    double getR() const;

    void setR(double r);

    const Point &getCenter() const;

    void setCenter(const Point &p);

    // 判断点和圆的关系
    void isInCircle(const Point &p) const;

private:
    double m_R;          // 半径
    Point m_Center;      // 圆心

};
