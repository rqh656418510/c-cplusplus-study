/**
 * 1. ����Ķ�̬�������ͷ�
 */

#include <iostream>

using namespace std;

class Teacher {
private:
    int _age;

public:
    Teacher(int age) {
        this->_age = age;
        cout << "���캯��������" << endl;
    }

    ~Teacher() {
        cout << "��������������" << endl;
    }

    void setAget(int age) {
        this->_age = age;
    }

    int getAge() {
        return this->_age;
    }
};

// C���Է������
void functionA() {
    int *p = (int *) malloc(sizeof(int));
    *p = 3;
    cout << "functionA -> p = " << *p << endl;
    free(p);
}

// C++�������
void functionB() {
    int *a = new int;
    *a = 3;
    cout << "functionB -> a = " << *a << endl;
    delete a;

    int *b = new int(30);
    cout << "functionB -> b = " << *b << endl;
    delete b;
}

// C���Է�������
void functionC() {
    char *p = (char *) malloc(sizeof(char) * 3);
    p[0] = 'a';
    p[1] = 'b';
    p[2] = 'c';
    cout << "functionC -> p = " << p[0] << p[1] << p[2] << endl;
    free(p);
}

// C++��������
void functionD() {
    char *p = new char[3];
    p[0] = 'e';
    p[1] = 'f';
    p[2] = 'g';
    cout << "functionD -> p = " << p[0] << p[1] << p[2] << endl;
    delete []p;
}

// C���Է������
void functionE() {
    // ���ﲻ���Զ�������Ĺ��캯������������
    Teacher *p = (Teacher *) malloc(sizeof(Teacher));
    p->setAget(33);
    cout << "functionE -> age = " << p->getAge() << endl;
    free(p);
}

// C++�������
void functionF() {
    // new��delete��ֱ��Զ�������Ĺ��캯������������
    Teacher *p = new Teacher(35);
    cout << "functionF -> age = " << p->getAge() << endl;
    delete p;
}

int main() {
    functionA();
    functionB();
    functionC();
    functionD();
    functionE();
    functionF();
    return 0;
}
