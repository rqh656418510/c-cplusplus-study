/**
 * 拷贝构造函数调用时机
 */

#include <iostream>

using namespace std;

class Person {

public:

    Person(const Person &p) {
        this->name = p.name;
        this->age = p.age;
        cout << "拷贝构造函数" << endl;
    }

private:
    string name;
    int age;

};

int main() {
    return 0;
}
