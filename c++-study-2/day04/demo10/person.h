/**
 * 模板的声明和实现，分开写在不同的源文件里
 */

#ifndef C___STUDY_PERSON_H
#define C___STUDY_PERSON_H

template<class T1, class T2>
class Person {

public:

    Person(T1 name, T2 age);

    void showPerson();

private:
    T1 m_Name;
    T2 m_Age;

};

#endif //C___STUDY_PERSON_H
