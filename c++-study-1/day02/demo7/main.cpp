/**
 * 1. 类的声明与类的实现分开写
 */


#include <iostream>
#include "Teacher.h"

using namespace std;

int main() {
    char name[32] = "Peter";
    Name teacher;
    teacher.setAge(10);
    teacher.setName(name);
    cout << "age: " << teacher.getAge() << endl;
    cout << "name: " << teacher.getName() << endl;
}