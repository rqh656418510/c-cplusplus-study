/**
 * 大厂C++开发工程师面试问题讲解
 */

#include <iostream>
#include <cstdarg>

using namespace std;

// 传统 C 风格的可变参数函数
void printNumbers(int num, ...) {
    va_list args;
    va_start(args, num); // 初始化 args，num 是可变参数的第一个参数
    for (int i = 0; i < num; i++) {
        int n = va_arg(args, int); // 获取下一个参数
        cout << n << " ";
    }
    va_end(args); // 清理
    cout << endl;
}

void test01() {
    printNumbers(3, 10, 20, 30);     // 输出：10 20 30
    printNumbers(5, 1, 2, 3, 4, 5);  // 输出：1 2 3 4 5
}

void test02() {
    struct Data {
        char a;
        double b;
    };
    cout << sizeof(Data) << endl;
}

int main() {
    test01();
    test02();
    return 0;
}
