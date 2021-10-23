/**
 * 1. ���캯���ĵ���
 */

#include <iostream>

using namespace std;

class Test {

private:
    int _a;
    int _b;

public:

    Test() {
        _a = 1;
        _b = 1;
    }

    Test(int a) {
        _a = a;
        _b = 3;
    }

    Test(int a, int b) {
        _a = a;
        _b = b;
    }


public:

    int getA() const {
        return _a;
    }

    int getB() const {
        return _b;
    }
};

int main() {
    // C++�����������޲ι��캯��
    Test t0;
    printf("a = %d, b = %d\n", t0.getA(), t0.getB());

    // C++�����������вι��캯��(�Ⱥŷ�)
    Test t1 = (1, 2, 3, 4, 5);
    printf("a = %d, b = %d\n", t1.getA(), t1.getB());

    // C++�����������вι��캯��(���ŷ�)
    Test t2(10, 20);
    printf("a = %d, b = %d\n", t2.getA(), t2.getB());

    // �ֶ����ù��캯������һ������(ֱ�ӵ��ù��캯����)
    Test t3 = Test(100, 200);
    printf("a = %d, b = %d\n", t3.getA(), t3.getB());

    return 0;
}
