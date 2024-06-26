/**
 * 类模板的分文件编写的问题以及解决方案
 * <p> 根本原因：由于类模版的成员函数是在运行阶段才去动态创建的，也就是说使用 `#include` 指令包含 ".h" 头文件时，编译器不会创建成员函数的具体实现，最终导致编译器出现无法解析外部命令的错误
 * <p> 解决方案一：类模板的声明和实现，都写到同一个源文件中，并将源文件的后缀名改为 ".hpp"，然后使用 `#include` 指令包含 ".hpp" 源文件，推荐使用此方式
 * <p> 解决方案二：类模板的声明和实现，分开写在不同的源文件，然后使用 `#include` 指令包含 ".cpp" 源文件，而不是包含 `.h` 头文件，不推荐使用此方式
 */

#include <iostream>
#include "person.hpp"       // 当模板的声明和实现，都写到同一个源文件时的引入方式
// #include "person.cpp"    // 当模板的声明和实现，分开写在不同的源文件时的引入方式

using namespace std;

int main() {
    Person<string, int> p("Peter", 10);
    p.showPerson();
    return 0;
}
