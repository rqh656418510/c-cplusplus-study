/*
 * 1. ������ʶ������Զ����������͵�ָ�룩
*/

#include <iostream>
#include <vector>

using namespace std;

class Person {

public:
    Person(int age, string name) {
        this->age = age;
        this->name = name;
    }

    int getAge() {
        return this->age;
    }

    string getName() {
        return this->name;
    }

private:
    int age;
    string name;

};

int main() {
    // ��������
    vector<Person *> v;

    // ��������
    v.push_back(new Person(23, "Jim"));
    v.push_back(new Person(26, "Tom"));
    v.push_back(new Person(29, "Peter"));

    // ��������
    for (vector<Person *>::iterator it = v.begin(); it != v.end(); it++) {
        cout << "age = " << (*it)->getAge() << ", name = " << (*it)->getName() << endl;
        // ����
        // cout << "age = " << (**it).getAge() << ", name = " << (**it).getName() << endl;
    }
    return 0;
}