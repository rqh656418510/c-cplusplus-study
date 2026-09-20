/**
 * 容器的说明和简单应用例续
 *
 * queue（队列）的使用
 */

#include <iostream>
#include <queue>

using namespace std;

class MyClass {
public:
    MyClass() : m_i(0) {
        std::cout << "MyClass()" << std::endl;
    }

    MyClass(int val) : m_i(val) {
        std::cout << "MyClass()" << std::endl;
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
    queue<MyClass> s;

    for (int i = 0; i < 3; ++i) {
        s.emplace(i);
    }

    for (int i = 0; i < 3; ++i) {
        MyClass& mc = s.front();
        cout << mc.m_i << endl;
        s.pop();
    }

    return 0;
}