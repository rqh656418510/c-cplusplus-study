/**
 * 左值、右值、左值引用、右值引用、move
 */

#include <iostream>

void test01() {
    int i = 10;

    // 错误写法，右值引用不能绑定左值
    // int &&refval = i;

    // 正确写法，std::move() 的作用：将一个左值强制转换为一个右值，这样就可以使用右值引用了
    int &&refval = std::move(i);

    i = 20;
    std::cout << "i = " << i << ", refval = " << refval << std::endl;

    refval = 25;
    std::cout << "i = " << i << ", refval = " << refval << std::endl;
}

void test02() {
    int &&refval = 10;

    // 错误写法，右值引用不能绑定左值
    // int &&refval2 = refval;

    // 正确写法，std::move() 的作用：将一个左值强制转换为一个右值，这样就可以使用右值引用了
    int &&refval2 = std::move(refval);

    refval = 30;
    std::cout << "refval = " << refval << ", refval2 = " << refval2 << std::endl;

    refval2 = 35;
    std::cout << "refval = " << refval << ", refval2 = " << refval2 << std::endl;
}

void test03() {
    std::string str = "I Love China";

    // 不会触发 std::string 的移动构造函数
    std::string &&str2 = std::move(str);

    std::cout << "str = " << str << ", &str = " << &str << std::endl;
    std::cout << "str2 = " << str2 << ", &str2 = " << &str2 << std::endl;

    // 会触发 std::string 的移动构造函数，即先申请一块新的内存空间，然后将 str 的内容拷贝到 str2，最后清空 str 的内容
    std::string str3 = std::move(str);

    std::cout << "str = " << str << ", &str = " << &str << std::endl;
    std::cout << "str3 = " << str3 << ", &str3 = " << &str3 << std::endl;
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}