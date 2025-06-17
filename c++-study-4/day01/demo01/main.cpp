/**
 * auto、头文件防卫、引用、常量
 */

#include <iostream>

using namespace std;

// auto 自动类型推导
void test01() {
    auto a = 3;

    int x = 5;
    int &ref = x;

    auto b = ref;       // b 是 int，不是 int&
    b = 6;
    cout << "x = " << x << ", b = " << b << endl;

    auto &c = ref;     // 若想保留引用，需要显式声明，c 是 int&，会改变 x
    c = 7;
    cout << "x = " << x << ", c = " << c << endl;
}

// constexpr 函数
constexpr int square(int x) {
    return x * x;
}

void test02() {
    int arr[square(4)];
}

int main() {
    test01();
    test02();
    return 0;
}
