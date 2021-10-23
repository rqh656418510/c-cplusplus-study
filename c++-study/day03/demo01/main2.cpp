/**
 * 1. ���캯���ķ��༰����
 */

#include <iostream>

using namespace std;

class Test {

private:
    int _a;
    int _b;

public:

    // �޲������캯��
    Test() {
        _a = 1;
        _b = 2;
        cout << "�����޲������캯��" << endl;
    }

    // �������Ĺ��캯��
    Test(int a, int b) {
        _a = a;
        _b = b;
        cout << "���ô������Ĺ��캯��" << endl;
    }

    // ��ֵ���캯��
    Test(const Test &obj) {
        _a = obj._a;
        _b = obj._b;
        cout << "���ø�ֵ���캯��" << endl;
    }

    int getA() const {
        return _a;
    }

    int getB() const {
        return _b;
    }

};

int main() {
    Test t1;
    printf("a = %d, b = %d\n", t1.getA(), t1.getB());

    Test t2 = Test(10, 20);
    printf("a = %d, b = %d\n", t2.getA(), t2.getB());

    Test t3 = Test(t1);
    printf("a = %d, b = %d\n", t3.getA(), t3.getB());

    return 0;
}