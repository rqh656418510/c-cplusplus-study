/**
 * 1. ���캯���ĳ�ʼ���б��ʹ��
 */

#include <iostream>

using namespace std;

class Teacher {

private :
    int _age;

public:

    Teacher(int age) {
        _age = age;
    }

    int getAge() const {
        return _age;
    }

};

class Student {

private :
    int _age;
    Teacher teacher;

public:

    int getAge() const {
        return _age;
    }

};

int main() {
    Teacher t(20);
    Student s;          // C++���������벻ͨ������ʾStudent��Ĭ�Ϲ��캯������ʽɾ������Ϊ����"mathTeacher"û��Ĭ�ϵĹ��캯��
    return 0;
}