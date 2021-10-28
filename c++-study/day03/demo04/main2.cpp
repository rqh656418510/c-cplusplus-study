/**
 * 1. 构造函数的初始化列表的使用
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

    // 使用构造函数的初始化列表来初始化Teacher类对象
    // 这里会自动调用Teacher类的有参构造函数，并将age2作为构造函数的参数传递过去
    Student(int age1, int age2) : teacher(age2) {
        _age = age1;
    }

    int getAge() const {
        return _age;
    }

    Teacher getTeacher() {
        return teacher;
    }

};

int main() {
    Student s(20, 35);
    cout << "student.age: " << s.getAge() << ", teacher.age: " << s.getTeacher().getAge() << endl;
    return 0;
}