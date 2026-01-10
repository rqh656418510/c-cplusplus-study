/**
 * 成员函数、对象拷贝、私有成员
 */

#include <iostream>

using namespace std;

// 定义类
class Student {
public:
    // 构造函数
    Student(int age, string name) : m_age(age), m_name(name) {
        cout << "Student()" << endl;
    }

    // 拷贝构造函数
    Student(const Student& s) {
        cout << "Student(const Student &)" << endl;
    }

    // 析构函数
    ~Student() {
        cout << "~Student" << endl;
    }

    // 成员函数
    void show() {
        cout << "age: " << m_age << ", name: " << m_name << endl;
    }

private:
    // 私有成员变量
    int m_age;
    string m_name;
};

void test01() {
    const char name[50] = "Peter";

    Student student(18, name);
    student.show();

    Student student2 = student;

    Student* pstudent = new Student(20, name);
    pstudent->show();
    delete pstudent;
}

int main() {
    test01();
    return 0;
}