/**
 * 模板的完全特例化和部分特例化
 */

#include <iostream>

using namespace std;

// 模板
template<typename T>
class MyVector {

public:
    MyVector() {
        cout << "MyVector init" << endl;
    }

};

// 模板完全特例化
// 针对 char * 类型提供完全特例化版本
template<>
class MyVector<char *> {

public:
    MyVector() {
        cout << "MyVector<char *> init" << endl;
    }

};

// 模板部分特例化
// 针对指针类型提供部分特例化版本
template<typename Ty>
class MyVector<Ty *> {

public:
    MyVector() {
        cout << "MyVector<Ty *> init" << endl;
    }

};

// 模板部分特例化
// 针对函数（有返回值，有两个参数）类型提供部分特例化版本
template<typename R, typename A1, typename A2>
class MyVector<R(A1, A2)> {

public:
    MyVector() {
        cout << "MyVector<R(A1, A2)> init" << endl;
    }

};

// 模板部分特例化
// 针对函数指针（有返回值，有两个参数）类型提供部分特例化版本
template<typename R, typename A1, typename A2>
class MyVector<R(*)(A1, A2)> {

public:
    MyVector() {
        cout << "MyVector<R(*)(A1, A2) init" << endl;
    }

};

int main() {
    MyVector<int> vec1;
    MyVector<char *> vec2;
    MyVector<int *> vec3;
    MyVector<int(int, int)> vec4;
    MyVector<int (*)(int, int)> vec5;
    return 0;
}