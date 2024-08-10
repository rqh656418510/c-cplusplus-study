/**
 * 类型转换-常量类型转换
 */
#include <iostream>

using namespace std;

void test01() {
    const int *p = nullptr;
    // 常量指针被转换成非常量指针
    int *newP = const_cast<int *>(p);

    int *p2 = nullptr;
    // 非常量指针被转换成常量指针
    const int *newP2 = const_cast<const int *> (p2);
}

void test02() {
    int age = 20;
    const int &ageRef = age;
    // 常量引用被转换成非常量引用
    int &ageRef2 = const_cast<int &>(ageRef);

    int num = 10;
    int &numRef = num;
    // 非常量引用被转换成常量引用
    const int &numRef2 = const_cast<const int &>(numRef);
}

void test03() {
    const int a = 10;
    // 不能直接对非指针和非引用的变量使用 const_cast 操作符去直接赋予或者去除它的 const 只读属性
    // int a = const_cast<int>(a);
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}
