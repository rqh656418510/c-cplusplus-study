/**
 * 1. 命名空间定义及使用语法
 */

#include <iostream>

using namespace std;

// 定义命名空间 NameSpaceA
namespace NameSpaceA {
    int a = 0;
}

// 定义命名空间 NameSpaceB
namespace NameSpaceB {
    int a = 1;

    // 嵌套定义命名空间 NameSpaceC
    namespace NameSpaceC {
        struct Teacher {
            char name[10];
            int age;
        };
    }
}

int main() {
    // 声明 std 命名空间后的写法
    cout << "hello world" << endl;

    // 不声明 std 命名空间后的写法
    std::cout << "hello world" << std::endl;

    // 声明 NameSpaceA 命名空间
    using namespace NameSpaceA;

    // 使用 NameSpaceC 命名空间中的变量
    using NameSpaceB::NameSpaceC::Teacher;

    // 命名空间可以起别名
    namespace NameSpaceD = NameSpaceB;

    printf("a = %d\n", a);
    printf("a = %d\n", NameSpaceB::a);
    printf("a = %d\n", NameSpaceD::a);

    Teacher teacher = {"Jim", 20};
    printf("teacher.age = %d\n", teacher.age);
    printf("teacher.name = %s\n", teacher.name);

    return 0;
}