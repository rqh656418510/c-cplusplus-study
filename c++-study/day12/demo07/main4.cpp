/*
 * 1. list容器的自定义数据类型操作
*/

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Person {

public:
    Person(string name, int age) {
        this->name = name;
        this->age = age;
    }

    string getName() {
        return this->name;
    }

    int getAge() {
        return this->age;
    }

private:
    string name;
    int age;

};

void printList(list<Person> &L) {
    // 遍历容器
    for (list<Person>::iterator it = L.begin(); it != L.end(); it++) {
        cout << "name: " << it->getName() << ", age: " << it->getAge() << endl;
    }
}

bool myCompare(Person &p1, Person &p2) {
    // 按年龄从大到小排序
    return p1.getAge() > p2.getAge();
}

int main() {
    list<Person> myList;

    Person p1("Tom", 17);
    Person p2("Jim", 18);
    Person p3("Peter", 19);

    cout << "------ list 插入操作（自定义数据类型） ------" << endl;

    myList.push_back(p1);
    myList.push_back(p2);
    myList.push_back(p3);
    printList(myList);

    cout << "------ list 排序操作（自定义数据类型） ------" << endl;

    myList.sort(myCompare);
    printList(myList);

    return 0;
}
