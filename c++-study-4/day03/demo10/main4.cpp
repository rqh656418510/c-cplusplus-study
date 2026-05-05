/**
 * 成员函数模板，显式实例化、声明
 *
 * (d) 模板显式实例化
 */

#include "MyClass.h"

int main() {
    MyClass<int> obj;
    obj.print(42);
    return 0;
}