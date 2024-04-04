/**
 * 模板的声明和实现，不要分开写在不同的源文件里，都写到同一个源文件中，并将源文件的后缀名改为 ".hpp"
 */

#ifndef C___STUDY_PERSON_HPP
#define C___STUDY_PERSON_HPP

#include <iostream>

using namespace std;

template<class T1, class T2>
class Person {

public:

    Person(T1 name, T2 age);

    void showPerson();

private:
    T1 m_Name;
    T2 m_Age;

};

template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
    this->m_Name = name;
    this->m_Age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson() {
    cout << "name = " << this->m_Name << ", age = " << this->m_Age << endl;
}

#endif //C___STUDY_PERSON_HPP
