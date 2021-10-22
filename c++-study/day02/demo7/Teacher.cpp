#include <iostream>
#include "Teacher.h"

using namespace std;

const char *Teacher::getName() const {
    return this->_name;
}

void Teacher::setName(char *name) {
    this->_name = name;
}

int Teacher::getAge() const {
    return this->_age;
}

void Teacher::setAge(int age) {
    this->_age = age;
}
