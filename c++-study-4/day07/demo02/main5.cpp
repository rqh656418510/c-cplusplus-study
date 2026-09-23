/**
 * 容器的说明和简单应用例续
 *
 * (e) forward_list（单向链表）使用
 */

#include <forward_list>
#include <iostream>

using namespace std;

class MyClass {
public:
    MyClass() : m_i(0) {
        std::cout << "MyClass()" << std::endl;
    }

    MyClass(const int val) : m_i(val) {
        std::cout << "MyClass(int val)" << std::endl;
    }

    MyClass(const MyClass& obj) : m_i(obj.m_i) {
        std::cout << "MyClass(const MyClass & obj)" << std::endl;
    }

    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }

public:
    int m_i;
};

int main() {
    forward_list<MyClass> list;

    for (int i = 0; i < 3; ++i) {
        cout << "---------- begin ----------" << endl;
        // 默认会调用 MyClass 的有参构造函数
        list.emplace_front(i);
        cout << "---------- end ------------" << endl;
    }

    int i = 1;
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        cout << "Object " << i << " address: " << &(*iter) << ", value: " << iter->m_i << endl;
        ++i;
    }

    return 0;
}