/*
 * 1. �쳣�������
 * a) ����Ĭ�ϵ��쳣������
*/

#include <iostream>

using namespace std;

// �Զ��� terminate() ����
void myTerminate() {
    cout << "���� myTerminate() �� terminate() ����!" << endl;
    exit(-1);
}

int divide(int x, int y) {
    return x / y;
}

int main() {
    // ����Ĭ�ϵ��쳣������
    set_terminate(myTerminate);

    int x = 10, y = 0, result;
    try {
        if (y == 0) {
            throw "������Ϊ��!";   //�׳��쳣���� terminate() ��������
        }
        else {
            result = x / y;
        }
    }
    // ���ᱻ�����쳣����
    catch (int e) {
        cout << "���������쳣!" << endl;
    }

    cout << "����������������!" << endl;
    return 0;
}