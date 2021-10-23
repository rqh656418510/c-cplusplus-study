/**
 * 1. 构造函数的调用
 */

#include <iostream>

using namespace std;

class Line {

private:
    double length;

public:

    // 构造函数声明
    Line(double len);

    // 成员函数声明
    double getLength(void);
    void setLength(double len);
};

// 构造函数定义
Line::Line(double len) {
    length = len;
}

// 成员函数定义
void Line::setLength(double len) {
    length = len;
}

double Line::getLength(void) {
    return length;
}

int main() {
    Line line(10.0);
    cout << "Length of line : " << line.getLength() << endl;

    line.setLength(6.0);
    cout << "Length of line : " << line.getLength() << endl;
    return 0;
}