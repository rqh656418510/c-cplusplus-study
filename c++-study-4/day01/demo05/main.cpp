/**
 * 函数新特性、内联函数、const详解
 */

#include <iostream>

using namespace std;

// 默认参数
void func1(string name, int age = 18) {
    cout << "name: " << name << ", age: " << age << endl;
}

// 未命名参数
int func2(int a, int) {
    return a * 2;
}

// 后置返回类型
auto func3(int a, int b) -> int {
    return a + b;
}

int main() {
    func1("Peter");
    func2(1, 3);
    func3(2, 4);
}