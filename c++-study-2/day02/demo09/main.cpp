/**
 * 面向对象设计案例 - 点和圆的关系
 */

#include <iostream>
#include "point.h"
#include "circle.h"

using namespace std;

int main() {
    Point p(11, 10);

    Point center(10, 0);
    Circle c(10, center);

    c.isInCircle(p);

    return 0;
}
