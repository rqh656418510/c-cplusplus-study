/**
 * 1. 作业案例-设计学生类
 */

#include <iostream>

using namespace std;

class Student {

public:
    Student() {

    }

    Student(long _id, string _name) : id(_id), name(_name) {

    }

    void setId(long id) {
        this->id = id;
    }

    void setName(string name) {
        this->name = name;
    }

    long getId() {
        return this->id;
    }

    string getName() {
        return this->name;
    }

    void toString() {
        cout << "id = " << this->getId() << ", name = " << this->getName() << endl;
    }

private:
    long id;
    string name;

};

int main() {
    Student s1(1, "Jim");
    s1.toString();

    Student s2;
    s2.setId(2);
    s2.setName("Tom");
    s2.toString();

    return 0;
}
