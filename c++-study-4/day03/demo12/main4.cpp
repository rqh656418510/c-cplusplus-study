/*
 * 模板全特化、偏特化(局部特化)
 *
 * (c) 类模板偏特化 - 从类模板的参数范围上进行偏特化
 */

#include <iostream>

using namespace std;

// 定义类模板（泛化版本）
template <typename T>
class TestClass {
public:
    TestClass() {
        cout << "TestClass() 泛化版本" << endl;
    }

    void print(T t) {
        cout << "printf(T) 泛化版本" << endl;
    }
};

// 类模板偏特化，从参数范围上进行偏特化（const T 的偏特化版本）
template <typename T>
class TestClass<const T> {
public:
    TestClass() {
        cout << "TestClass() 偏特化版本" << endl;
    }

    void print(T t) {
        cout << "printf(const T) 偏特化版本" << endl;
    }
};

// 类模板偏特化，从参数范围上进行偏特化（T * 的偏特化版本）
template <typename T>
class TestClass<T *> {
public:
    TestClass() {
        cout << "TestClass() 偏特化版本" << endl;
    }

    void print(T *t) {
        cout << "printf(T *) 偏特化版本" << endl;
    }
};

// 类模板偏特化，从参数范围上进行偏特化（T & 的偏特化版本）
template <typename T>
class TestClass<T &> {
public:
    TestClass() {
        cout << "TestClass() 偏特化版本" << endl;
    }

    void print(T &t) {
        cout << "printf(T &) 偏特化版本" << endl;
    }
};

// 类模板偏特化，从参数范围上进行偏特化（T && 的偏特化版本）
template <typename T>
class TestClass<T &&> {
public:
    TestClass() {
        cout << "TestClass() 偏特化版本" << endl;
    }

    void print(T &&t) {
        cout << "printf(T &&) 偏特化版本" << endl;
    }
};

int main() {
    int num1 = 10;
    const int num2 = 20;
    int &num3 = num1;  // 左值引用

    // 使用泛化版本
    TestClass<int> t1;  // 这是泛化对象
    t1.print(1);

    // 使用 <const T> 偏特化版本
    TestClass<const int> t2;  // 这是偏特化对象
    t2.print(num2);

    // 使用 <T *> 偏特化版本
    TestClass<int *> t3;  // 这是偏特化对象
    t3.print(&num1);

    // 使用 <T &> 偏特化版本
    TestClass<int &> t4;  // 这是偏特化对象
    t4.print(num3);

    // 使用 <T &&> 偏特化版本
    TestClass<int &&> t5;  // 这是偏特化对象
    t5.print(move(num3));

    return 0;
}