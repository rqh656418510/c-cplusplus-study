/**
 * 1. C++�е���ķ�װ
 */

#include <iostream>

using namespace std;

class Circle {

private:
    double m_r; // Բ�εİ뾶
    double m_s; // Բ�ε����

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
    cout << "������Բ�εİ뾶��";
    cin >> r;

    Circle circle;
    circle.setR(r);
    cout << "Բ�ε�����ǣ�" << circle.getS() << endl;
    return 0;
}
