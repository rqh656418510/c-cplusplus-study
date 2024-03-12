/**
 * 面向对象设计案例 - 设计立方体类
 */

#include <iostream>

using namespace std;

// 立方体类
class Cube {

public:
    double getLength() const {
        return m_Length;
    }

    double getWidth() const {
        return m_Width;
    }

    double getHeight() const {
        return m_Height;
    }

    void setLength(double l) {
        this->m_Length = l;
    }

    void setWidth(double w) {
        this->m_Width = w;
    }

    void setHeight(double h) {
        this->m_Height = h;
    }

    double getArea() {
        double area = 2 * m_Length * m_Width + 2 * m_Width * m_Height + 2 * m_Length * m_Height;
        return area;
    }

    double getVolume() {
        double volume = m_Length * m_Width * m_Height;
        return volume;
    }

    // 成员函数判断两个立方体是否相等
    double compare(const Cube &c) const {
        return this->m_Length == c.getLength() && this->m_Width == c.getWidth() && this->m_Height == c.getHeight();
    }

private:
    double m_Length;
    double m_Width;
    double m_Height;

};

// 全局函数判断两个立方体是否相等
bool compareCube(const Cube &c1, const Cube &c2) {
    return c1.getLength() == c2.getLength() && c1.getWidth() == c2.getWidth() && c1.getHeight() == c2.getHeight();
}

int main() {
    Cube c1;
    c1.setLength(10);
    c1.setWidth(10);
    c1.setHeight(10);
    cout << "area = " << c1.getArea() << endl;
    cout << "volume = " << c1.getVolume() << endl;

    Cube c2;
    c2.setLength(11);
    c2.setWidth(10);
    c2.setHeight(10);
    cout << "area = " << c2.getArea() << endl;
    cout << "volume = " << c2.getVolume() << endl;

    bool result1 = compareCube(c1, c2);
    cout << "compare result is " << (result1 ? "yes" : "no") << endl;

    bool result2 = c1.compare(c2);
    cout << "compare result is " << (result2 ? "yes" : "no") << endl;

    return 0;
}
