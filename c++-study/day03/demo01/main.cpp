/**
 * 1. ���캯�������������Ķ���
 */

#include <iostream>

using namespace std;

class Teacher {

public:

    // �����޲ι��캯��
    Teacher() {
        cout << "���ù��캯��" << endl;
    }

    // ������������
    ~Teacher() {
        cout << "������������" << endl;
    }

};

int main() {
    Teacher teacher;
    return 0;
}