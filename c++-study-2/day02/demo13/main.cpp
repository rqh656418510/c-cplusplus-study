/**
 * 构造函数的调用规则
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

int main() {
    return 0;
}
