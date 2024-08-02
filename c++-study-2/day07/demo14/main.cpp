/**
 * 类模板的应用-数组类的封装
 */

#include <iostream>
#include "MyArray.hpp"

using namespace std;

// 自定义数据类型
class Person {

public:
    Person() {
        this->m_Name = "";
        this->m_age = 0;
    }

    Person(string name, int age) {
        this->m_Name = name;
        this->m_age = age;
    }

    // << 操作符重载
    friend ostream &operator<<(ostream &out, const Person &person) {
        cout << "name = " << person.m_Name << ", age = " << person.m_age;
        return out;
    }

private:
    string m_Name;
    int m_age;

};

void test01() {
    MyArray<int> array(10);

    for (int i = 0; i < 10; i++) {
        array.pushBack(i);
    }

    cout << array << endl;
    cout << array[3] << endl;
    cout << "capacity = " << array.capacity() << endl;
    cout << "size = " << array.size() << endl;
}

void test02() {
    MyArray<int> array1(10);
    for (int i = 0; i < 10; i++) {
        array1.pushBack(i);
    }
    cout << array1 << endl;

    // 调用拷贝构造函数
    MyArray<int> array2 = array1;
    cout << array2 << endl;
}

void test03() {
    Person p1("A", 20);
    Person p2("B", 20);
    Person p3("C", 20);
    Person p4("D", 20);

    MyArray<Person> array(4);
    array.pushBack(p1);
    array.pushBack(p2);
    array.pushBack(p3);
    array.pushBack(p4);

    cout << array << endl;
}

int main() {
    cout << "------- test01() -------" << endl;
    test01();

    cout << "------- test02() -------" << endl;
    test02();

    cout << "------- test03() -------" << endl;
    test03();

    return 0;
}
