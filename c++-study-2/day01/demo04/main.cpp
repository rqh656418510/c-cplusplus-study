/**
 * 1. using 声明与 using 编译指令
 */

#include <iostream>

using namespace std;

// 定义命名空间
namespace NameSpaceA {
    int age = 10;
}

// using 声明
void test01() {
    int age = 20;

    // 这里使用 using 声明后，编译器会编译失败，因为存在二义性
    // 因为使用 using 声明后，以后看到的 age 默认就是用 NameSpaceA 命名空间下的 age
    // 但是编译器又有就近原则，也就是此时出现了二义性，导致编译器会编译失败
    // using NameSpaceA::age;

    cout << "age = " << age << endl;
}

// using 编译指令
void test02() {
    int age = 30;

    // 使用 using 编译指令，不会产生二义性
    // 因为 using 编译指令的优先级低于编译器的就近原则
    using namespace NameSpaceA;

    cout << "age = " << age << endl;
}

int main() {
    test01();
    test02();
    return 0;
}
