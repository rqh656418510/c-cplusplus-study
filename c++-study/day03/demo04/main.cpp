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

    int getAge() const {
        return _age;
    }

};

int main() {
    Teacher t(20);
    Student s;          // C++编译器编译不通过，提示Student的默认构造函数被隐式删除，因为属性"mathTeacher"没有默认的构造函数
    return 0;
}