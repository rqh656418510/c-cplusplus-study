/**
 * 1. ʹ�ù��캯���ĳ�ʼ���б���ʼ�� const ��Ա�����ó�Ա
 */

#include <iostream>

using namespace std;

class A {
private:
    int i;
    int &j;
    const int c;

public:

    A(int x) {
        i = -1;
        c = 5;    // C++���벻ͨ��������ͨ����ʼ���б�����ʼ��
        j = x;    // C++���벻ͨ��������ͨ����ʼ���б�����ʼ��
    }
};

int main() {
    A a(3);
    return 0;
}