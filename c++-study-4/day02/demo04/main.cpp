/**
 * 类内初始化、默认构造函数、=default
 */

#include <iostream>

using namespace std;

// 定义类
class Student {
public:
    // 默认构造函数的另一种写法
    // Student() = default;

    // 默认构造函数（无参）
    Student() {
        cout << "Student()" << endl;
    }

    // 有参构造函数（一个参数）
    explicit Student(int age) : m_age(age), m_name("") {
        cout << "Student(int)" << endl;
    }

    // 有参构造函数（两个参数）
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
    int getAge() const {
        return m_age;
    }

    // 成员函数
    string getName() const {
        return m_name;
    }

    // 成员函数
    void show() const {
        cout << "age: " << m_age << ", name: " << m_name << endl;
    }

private:
    int m_age = 0;
    string m_name = "";
};

int main() {
    Student student;
    return 0;
}