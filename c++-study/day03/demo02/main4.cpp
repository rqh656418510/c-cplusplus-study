/**
 * 1. �������캯���ĵ����ֵ��ó���
 */

#include <iostream>

using namespace std;

class Location {

private :
    int x, y;

public:
    Location(int xx = 0, int yy = 0) {
        x = xx;
        y = yy;
        cout << "�вι��캯����������" << endl;
    }

    Location(const Location &p) {
        x = p.x;
        y = p.y;
        cout << "�������캯����������" << endl;
    }

    ~Location() {
        cout << "����������������" << endl;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
};

Location functionA() {
    Location l(1, 2);
    return l;
}

int main() {
    // ��������functionA()���ص��������󣬸�ֵ������һ��ͬ���͵Ķ�����ô��������ᱻ����
    // ��ʱ�вι��캯����������������������
    Location A;
    A = functionA();

    // ��ʹ�ú���functionA()��������������ʼ������һ��ͬ���͵Ķ�����ô���������ֱ��ת���µĶ���
    // ��ʱ�вι��캯��������������������һ��
    // Location B = functionA();
    return 0;
}