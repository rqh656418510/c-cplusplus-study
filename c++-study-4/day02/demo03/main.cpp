/**
 * inline、const、mutable、this、stat
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
        m_age += 1;
        return m_age;
    }

    // 成员函数
    string getName() const {
        return m_name;
    }

    // 成员函数
    void show() const {
        cout << "age: " << m_age << ", name: " << m_name << "m_total: " << m_total << endl;
    }

    // 返回自身对象的引用（为了支持链式调用）
    Student& increAge() {
        m_age += 1;
        return *this;
    }

    // 成员函数
    void updateTotal(int total) {
        m_total = total;
    }

    // 静态成员函数
    static void print() {
        cout << "invoke print()" << endl;
    }

private:
    mutable int m_age;  // 可变成员变量
    string m_name;
    static int m_total;  // 静态成员变量（这里只是声明，还没有分配内存；特别注意：不允许在类内初始化非常量静态成员变量
};

// 类内声明的 static 成员变量，必须在类外提供一次定义（不需要使用 static 修饰）
int Student::m_total = 0;

int main() {
    Student student1(18, "Jim");
    student1.updateTotal(1);
    student1.increAge().increAge().increAge();
    student1.show();

    Student student2(20, "Peter");
    student2.updateTotal(3);
    student2.show();

    student1.show();

    Student::print();

    return 0;
}