/**
 * 1. �������캯���ĵ�һ�ֵ��ó���
 */

#include <iostream>

using namespace std;

class Test {

private :
    int _a;

public:
    Test() {
        cout << "�޲ι��캯���Զ���������" << endl;
    }

    Test(int a) {
        _a = a;
        cout << "�вι��캯����������" << endl;
    }

    Test(const Test &obj) {
        _a = obj._a + 10;
        cout << "�������캯����������" << endl;
    }

    ~Test() {
        cout << "����������������" << endl;
    }

    int getA() {
        return _a;
    }
};

void functionA() {
    Test t1(1);
    Test t0(2);
    t0 = t1;            // ��ͨ�ĸ�ֵ�������������캯�����ᱻ����
    Test t2 = t1;       // ��ĳ�ʼ������(�Ⱥŷ�)���������캯���ᱻ����
    cout << "a = " << t2.getA() << endl;
}

int main() {
    functionA();
    return 0;
}