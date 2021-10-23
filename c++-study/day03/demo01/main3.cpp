/**
 * 1. ���캯���ĵ���
 */

#include <iostream>

using namespace std;

class Line {

private:
    double length;

public:

    // ���캯������
    Line(double len);

    // ��Ա��������
    double getLength(void);
    void setLength(double len);
};

// ���캯������
Line::Line(double len) {
    length = len;
}

// ��Ա��������
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