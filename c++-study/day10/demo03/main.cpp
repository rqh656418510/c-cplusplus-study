/*
 * 1. �쳣�������
 * a) �쳣�ڼ̳��е�ʹ��
*/

#include "MyArray.h"

int main() {
    try {
        // ���ù��캯��
        MyArray array1(-6);
        // MyArray array1(5);
        // MyArray array1(0);
        // MyArray array1(2000);

        // ��������� "[]"
        for (int i = 0; i < array1.getsize(); i++) {
            array1[i] = 20 + i;
        }

        // ��������� "<<"
        cout << array1 << endl;

        // ���ÿ������캯��
        MyArray array2 = array1;
        cout << array2 << endl;

        MyArray array3(3);
        array3[0] = 43;
        array3[1] = 56;
        array3[2] = 79;
        cout << array3 << endl;

        // ��������� "="
        array3 = array2;
        cout << array3 << endl;

    }
    // ʹ�����ò����쳣����̬��
    catch (SizeException& e) {
        e.printErr();
    }
    catch (...) {
        cout << "����δ֪�쳣" << endl;
    }
    return 0;
}