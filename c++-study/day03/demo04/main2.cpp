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

    // ʹ�ù��캯���ĳ�ʼ���б�����ʼ��Teacher�����
    // ������Զ�����Teacher����вι��캯��������30��Ϊ���캯���Ĳ������ݹ�ȥ
    Student(int age) : teacher(30) {
        _age = age;
    }

    int getAge() const {
        return _age;
    }

    Teacher getTeacher() {
        return teacher;
    }

};

int main() {
    Student s(20);
    cout << "student.age: " << s.getAge() << ", teacher.age: " << s.getTeacher().getAge() << endl;
    return 0;
}