/**
 * 1. ���캯���ķ���
 */

#include <iostream>

using namespace std;

class Test {

private:
    int _a;
    int _b;

public:

    // �޲����Ĺ��캯��
    Test() {
        _a = 1;
        _b = 2;
    }

    // �������Ĺ��캯��
    Test(int a, int b) {
        _a = a;
        _b = b;
    }

    // ��ֵ���캯��
    Test(const Test &obj) {
        _a = obj._a;
        _b = obj._b;
    }

};