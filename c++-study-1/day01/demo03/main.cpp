/**
 * 1. 计算圆形的面积，采用面向对象的编程方式
 */

#include <iostream>

using namespace std;

class Circle {

public:
    double m_r; // 圆形的半径
    double m_s; // 圆形的面积

public:
    void setR(double r) {
        m_r = r;
    }

    double getR() {
        return m_r;
    }

    double getS() {
        m_s = 3.14 * m_r * m_r;
        return m_s;
    }

};

int main() {
    double r;
    cout << "请输入圆形的半径：";
    cin >> r;

    Circle circle;
    circle.setR(r);
    cout << "圆形的面积是：" << circle.getS() << endl;
    return 0;
}