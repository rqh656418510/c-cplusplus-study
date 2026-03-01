/*
 * 友元函数、友元类、友元成员函数
 */

#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Human {
public:
    Human() {
        cout << "Human::Human()" << endl;
    }

    Human(const string& name, int age) : m_Name(name), m_Age(age) {
        cout << "Human::Human(string, int)" << endl;
    }

    ~Human() {
        cout << "Human::~Human()" << endl;
    }

    void eat() const {
        cout << m_Name << "Human eat food" << endl;
    }

public:
    // 声明友元函数
    friend void show(const Human& human);

private:
    int m_Age;
    string m_Name;
};

// 友元函数
void show(const Human& human) {
    // 在友元函数中，可以访问其他类的私有成员变量或者私有成员函数
    cout << "name = " << human.m_Name << ", age = " << human.m_Age << endl;
}

int main() {
    Human human("Jim", 18);
    show(human);
    return 0;
}