/**
 * 1. ǳ���������
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

int main() {
    return 0;
}