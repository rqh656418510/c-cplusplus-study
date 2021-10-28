#include <iostream>
#include "Teacher.h"

using namespace std;

const char *Name::getName() const {
    return this->_name;
}

void Name::setName(char *name) {
    this->_name = name;
}

int Name::getAge() const {
    return this->_age;
}

void Name::setAge(int age) {
    this->_age = age;
}
