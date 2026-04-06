/**
 * 模板概念，函数模板定义、调用
 *
 * (b) 非类型模板参数
 */

#include <cstring>
#include <iostream>

using namespace std;

// 定义函数模板（使用非类型模板参数）
template <int A, int B>
int sum() {
    return A + B;
}

// 定义函数模板（使用非类型模板参数）
template <unsigned L1, unsigned L2>
int charscomp(const char (&c1)[L1], const char (&c2)[L2]) {
    return strcmp(c1, c2);
}

// 定义函数模板（使用类型模板参数和非类型模板参数）
template <typename T, int A>
void repeatPrint(T value) {
    for (int i = 0; i < A; ++i) {
        cout << value << " ";
    }
    cout << endl;
}

void test01() {
    cout << "========== test01() ======" << endl;
    // 显式指定非类型模板参数
    int result1 = sum<3, 5>();
    cout << result1 << endl;
}

void test02() {
    cout << "========== test02() ======" << endl;
    // 编译器会自动推断非类型模板参数
    int result1 = charscomp("test2", "test");
    cout << result1 << endl;
}

void test03() {
    cout << "========== test03() ======" << endl;
    // T 被推断为 int，而 A 显式指定为 2
    repeatPrint<int, 2>(10);

    // T 被推断为 double，而 A 显式指定为 3
    repeatPrint<double, 3>(3.14);

    // T 被推断为 const char*，而 A 显式指定为 4
    repeatPrint<const char*, 4>("Hi");
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}