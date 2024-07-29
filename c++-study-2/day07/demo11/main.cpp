/**
 * 类模板的分文件编写问题以及解决
 *
 * <p> 类模板的声明和实现，建议都写到同一个源文件中，并将源文件的后缀名改为 .hpp，然后使用 #include 指令包含 .hpp 源文件。
 */
#include <iostream>
#include "Person.hpp"

using namespace std;

int main() {
    Person<string, int> p("Tom", 23);
    p.showPerson();
    return 0;
}