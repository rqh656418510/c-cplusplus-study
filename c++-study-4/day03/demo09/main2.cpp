/**
 * typename场合、默认模板参数、趣味写法分析
 *
 * (b) 函数模板的趣味写法
 */

#include <iostream>

using namespace std;

// 定义函数指针类型（第一种写法，C 语义风格）
typedef int (*FunType)(int, int);

// 定义函数指针类型（第二种写法，C++ 现代写法）
// using FunType = int(*)(int, int);

// 定义函数模板（支持使用函数指针或函数对象作为其他函数的参数）
template <typename T, typename F>
int testFunc(const T &i, const T &j, F func) {
    return func(i, j);
}

// 定义普通函数
int sum(int a, int b) {
    return a + b;
}

// 定义函数对象（仿函数），重载了 operator()，可以像函数一样使用对象
class Test {
public:
    // 构造函数
    Test() {
        cout << "Test()" << endl;
    }

    // 析构函数
    ~Test() {
        cout << "~Test()" << endl;
    }

    // 拷贝构造函数
    Test(const Test &t) {
        cout << "Test(const Test&)" << endl;
    }

    // 重载圆括号操作符
    int operator()(int i, int j) const {
        return i + j;
    }
};

void test01() {
    cout << "------------ test01() ---------------" << endl;

    // 函数指针作为其他函数的参数
    int result = testFunc(1, 3, sum);
    cout << result << endl;
}

void test02() {
    cout << "------------ test02() ---------------" << endl;

    // 定义函数对象（可调用对象）
    Test obj;

    // 函数对象作为其他函数的参数（会额外调用 Test 类的拷贝构造函数）
    int result2 = testFunc(5, 6, obj);
    cout << result2 << endl;
}

void test03() {
    cout << "------------ test03() ---------------" << endl;

    // 函数对象作为其他函数的参数（更高效的写法，直接使用临时对象，不会额外调用 Test 类的拷贝构造函数）
    int result3 = testFunc(7, 8, Test());
    cout << result3 << endl;
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}