/**
 * typename场合、默认模板参数、趣味写法分析
 *
 * (c) 默认模板参数的使用
 */

#include <stdexcept>
#include <iostream>

using namespace std;

// 定义函数模板（使用默认模板参数）
template <typename T>
T add(T a, T b = 10) {
    return a + b;
}

// 定义函数模板（函数参数设置默认值）
template <typename T = int>
T sum(T a, T b = 10) {
    return a + b;
}

// 定义类模板（使用默认模板参数）
template <typename T, size_t size = 10>
class MyArray {
public:
    // 重载 [] 操作运算符，返回非 const 对象
    T& operator[](size_t index) {
        if (index < 0 || index > size - 1) {
            throw out_of_range("index out of range");
        }
        return array[index];
    }

    // 重载 [] 操作运算符，返回 const 对象
    const T& operator[](size_t index) const {
        if (index < 0 || index > size - 1) {
            throw out_of_range("index out of range");
        }
        return array[index];
    }

private:
    T array[size];
};

void test01() {
    cout << add(1, 2) << endl;              // 使用默认 T=int
    cout << add<double>(1.5, 2.3) << endl;  // 指定 T=double
}

void test02() {
    cout << sum(5, 3) << endl;  // 8
    cout << sum(5) << endl;     // 15（b 使用默认值 10）
}

void test03() {
    MyArray<int> array;  // size = 10
    array[0] = 10;
    array[1] = 20;
    cout << array[0] << ", " << array[1] << endl;

    MyArray<int, 5> array2;  // size = 5
    array2[0] = 40;
    array2[1] = 50;
    cout << array2[0] << ", " << array2[1] << endl;
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}