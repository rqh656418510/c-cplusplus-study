/**
 * 拷贝构造函数的调用时机
 */

#include <iostream>

using namespace std;

class Person {

public:
    Person() {
        cout << "无参构造函数" << endl;
    }

    Person(string name, int age) {
        this->name = name;
        this->age = age;
        cout << "有参构造函数" << endl;
    }

    Person(const Person &p) {
        this->name = p.name;
        this->age = p.age;
        cout << "拷贝构造函数" << endl;
    }

    ~Person() {
        cout << "析构函数" << endl;
    }

    int getAge() const {
        return this->age;
    }

    void setAge(int age) {
        this->age = age;
    }

private:
    string name;
    int age;

};

void doWork(Person p) {
    p.setAge(28);
}

void test01() {
    Person p1("Jim", 23);

    // 第一种情况：自动调用拷贝构造函数
    Person p2 = p1;

    // 第二种情况：自动调用拷贝构造函数
    Person p3(p1);

    // 第三种情况：自动调用拷贝构造函数
    Person p4 = Person(p1);
}

void test02() {
    Person p("Tom", 14);

    // 第四种情况：自动调用拷贝构造函数，以值传递的方式给函数参数传值
    doWork(p);

    cout << "age = " << p.getAge() << endl;
}

int main() {
    cout << "----------call test1()----------" << endl;
    test01();

    cout << "----------call test2()----------" << endl;
    test02();
    return 0;
}
