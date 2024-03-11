/**
 * 深拷贝与浅拷贝
 */

#include <iostream>

using namespace std;

class Person {

public:

    Person(string name, int age) {
        this->name = name;
        this->age = age;
        cout << "有参构造函数" << endl;
    }

    ~Person() {
        cout << "析构函数" << endl;
    }

    string getName() const {
        return this->name;
    }

    int getAge() const {
        return this->age;
    }

private:
    string name;
    int age;

};

int main() {
    return 0;
}
