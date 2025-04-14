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

    // 获取名称
    string getName() const {
        return this->name;
    }

    // 获取年龄
    int getAge() const {
        return this->age;
    }

    // 重载 == 双等号操作符
    bool operator==(const Person &p) {
        return this->name == p.name && this->age == p.age;
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
    Person p4("David", 20);

    cout << "------ list 插入操作（自定义数据类型） ------" << endl;

    myList.push_back(p1);
    myList.push_back(p2);
    myList.push_back(p3);
    myList.push_back(p4);
    printList(myList);

    cout << "------ list 删除操作（自定义数据类型） ------" << endl;

    // 调用 remove() 函数移除 list 容器中的元素时，自定义数据类型必须重载 `==` 双等号操作符，否则移除操作会执行失败
    myList.remove(p3);
    printList(myList);

    cout << "------ list 排序操作（自定义数据类型） ------" << endl;

    // 对 list 的自定义类型数据类型进行排序时，必须指定排序规则
    myList.sort(myCompare);
    printList(myList);

    return 0;
}
