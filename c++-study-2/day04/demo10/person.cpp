/**
 * 类模板的声明和实现，分开写在不同的源文件里
 */

#include <iostream>
#include "person.h"

using namespace std;

template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
    this->m_Name = name;
    this->m_Age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson() {
    cout << "name = " << this->m_Name << ", age = " << this->m_Age << endl;
}
