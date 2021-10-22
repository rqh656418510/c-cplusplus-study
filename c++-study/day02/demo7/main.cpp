#include <iostream>
#include "Teacher.h"

using namespace std;

int main() {
    char name[32] = "Peter";
    Teacher teacher;
    teacher.setAge(10);
    teacher.setName(name);
    cout << "age: " << teacher.getAge() << endl;
    cout << "name: " << teacher.getName() << endl;
}