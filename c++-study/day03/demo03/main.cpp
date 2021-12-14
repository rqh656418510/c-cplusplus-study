/**
 * 1. ǳ���������
 * �����������Ĵ����У�û���Զ��忽�����캯����ʹ�õ��� C++ �������ṩ��Ĭ�Ͽ������캯������˳����޷���������
 * ��ɳ����޷��������еĸ���ԭ���ǣ�C++ �ṩ��Ĭ�Ͽ������캯������ǳ�������ڵ����������������ʱ����ִ���ͬһ���ڴ�ռ䱻�ͷ����Σ�
 */

#include <iostream>
#include "string.h"

using namespace std;

class Name {

private:
    char *p;
    int len;

public:

    Name(const char *name) {
        cout << "�вι��캯����������" << endl;
        int length = strlen(name);
        p = (char *) malloc(length + 1);
        strcpy(p, name);
        len = length;
    }

    ~Name() {
        cout << "����������������" << endl;
        if (p != NULL) {
            free(p);
            p = NULL;
            len = 0;
        }
    }

    char *getP() const {
        return p;
    }

    int getLen() const {
        return len;
    }
};

int main() {
    Name obj1("Peter");
    Name obj2 = obj1;       // �Զ�����C++�ṩ��Ĭ�Ͽ������캯��������ǳ����
    cout << "obj1.name: " << obj1.getP() << ", obj1.len:  " << obj1.getLen() << endl;
    cout << "obj2.name: " << obj2.getP() << ", obj2.len:  " << obj2.getLen() << endl;
    return 0;
}