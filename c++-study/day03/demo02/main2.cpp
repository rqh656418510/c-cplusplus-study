/**
 * 1. �������캯���ĵ����ֵ��ó���
 */

#include "iostream"

using namespace std;

class Location {
private :
    int X, Y;

public:
    Location(int xx = 0, int yy = 0) {
        X = xx;
        Y = yy;
        cout << "�вι��캯����������" << endl;
    }

    Location(const Location &p) {
        X = p.X;
        Y = p.Y;
        cout << "�������캯����������" << endl;
    }

    ~Location() {
        cout << "����������������" << endl;
    }

    int getX() {
        return X;
    }

    int getY() {
        return Y;
    }
};

void functionA(Location l) {
    cout << l.getX() << "," << l.getY() << endl;
}

int main() {
    Location l(1, 2);
    functionA(l);         // �������캯���ᱻ���ã������ʹ��ʵ�α�����ʼ���βα�����ͬʱ��ഴ��һ��Location��������������������ᱻ��������
    return 0;
}
