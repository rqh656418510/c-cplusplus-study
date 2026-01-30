/**
 * 拷贝构造函数
 */

#include <iostream>

using namespace std;

// 定义类
class Student {
public:
    // 无参构造函数
    Student() : m_age(0), m_name("") {
        cout << "Student()" << endl;
    }

    // 有参构造函数
    Student(int age, string name) : m_age(age), m_name(name) {
        cout << "Student(int, string)" << endl;
    }

    // 拷贝构造函数
    Student(const Student& s) {
        cout << "Student(const Student &)" << endl;
        m_age = s.m_age;
        m_name = s.m_name;
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

void func(Student s) {
    s.show();
}

Student func2() {
    Student student1(22, "David");
    return student1;
}

void test01() {
    Student student1(20, "Peter");

    // 拷贝对象（会调用拷贝构造函数）的多种写法
    Student student2 = student1;
    Student student3(student1);
    Student student4{student1};
    Student student5 = (student1);
    Student student6 = {student1};
}

void test02() {
    // 将一个对象作为实参传递给一个非引用类型的形参，也会发生对象拷贝，即调用拷贝构造函数
    Student student1(18, "Jim");
    func(student1);
}

void test03() {
    // 大多数情况下，这里不会调用拷贝构造函数，因为会发生 NRVO（命名返回值优化），但这是 "允许优化"，不是强制
    // 在 C++ 17 及之后，函数返回局部对象时会强制进行拷贝消除（RVO/NRVO），对象会被直接构造在调用者的栈空间中，不存在中间临时对象，因此不会调用拷贝构造函数
    Student s = func2();
}

int main() {
    // test01();
    test02();
    // test03();
    return 0;
}