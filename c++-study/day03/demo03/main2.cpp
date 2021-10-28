/**
 * 1. ǳ���������
 * �Զ��忽�����캯����ͨ��ʵ������������µ��ڴ�ռ䣩�����C++Ĭ�Ͽ������캯����ǳ��������
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

    // �����ʵ��
    Name(const Name &name) {
        cout << "�������캯����������" << endl;
        int length = name.getLen();
        p = (char *) malloc(length + 1);
        strcpy(p, name.getP());
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
    Name obj3 = obj1;       // �Զ������Զ���Ŀ������캯��
    cout << "obj1.name: " << obj1.getP() << ", obj1.len:  " << obj1.getLen() << endl;
    cout << "obj3.name: " << obj3.getP() << ", obj3.len:  " << obj3.getLen() << endl;
    return 0;
}