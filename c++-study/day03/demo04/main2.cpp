/**
 * 1. ���캯���ĳ�ʼ���б�
 */

#include <iostream>

using namespace std;

class A {

private:
    int i;
    int &j;
    const int c;

public:

    // ���캯����ʼ���б�
    A(int x, int y) : c(x), j(y) {
        i = -1;
    }

};

int main() {
    int m;
    A a(5, m);  // C++�������ͨ��
    return 0;
}