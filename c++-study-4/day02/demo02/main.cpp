/**
 * 构造函数详解，explicit，初始化列表
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

// 构造函数的调用
void test01() {
    // 创建类对象（会调用无参构造函数）的多种写法
    Student student1;
    Student student2 = Student();
    Student student3();
    Student student4 = Student{};
    Student student5{};
    Student student6 = {};

    // 创建类对象（会调用有参构造函数）的多种写法
    Student student7 = Student(18, "Peter");
    Student student8(18, "Peter");
    Student student9 = Student{18, "Peter"};
    Student student10{18, "Peter"};
    Student student11 = {18, "Peter"};
}

// 拷贝构造函数的调用
void test02() {
    Student student1;

    // 拷贝对象（会调用拷贝构造函数）的多种写法
    Student student2 = student1;
    Student student3(student1);
    Student student4{student1};
    Student student5 = (student1);
    Student student6 = {student1};
}

int main() {
    // test01();
    // test02();
    return 0;
}
