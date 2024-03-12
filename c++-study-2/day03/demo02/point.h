#pragma once

class Point {

// 点
public:
    Point();

    Point(double x, double y);

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

private:
    double m_X;

    double m_Y;

};
