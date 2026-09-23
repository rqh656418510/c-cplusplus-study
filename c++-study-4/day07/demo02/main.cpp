/**
 * 容器的说明和简单应用例续
 *
 * (a) deque 容器使用
 */

#include <deque>
#include <iostream>

using namespace std;

class MyClass {
public:
    MyClass() {
        std::cout << "MyClass()" << std::endl;
    }

    MyClass(const MyClass& obj) {
        std::cout << "MyClass(const MyClass & obj)" << std::endl;
    }

    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }

private:
    int m_i = 0;
};

int main() {
    deque<MyClass> deq;

    for (int i = 0; i < 3; ++i) {
        cout << "---------- begin ----------" << endl;
        deq.emplace_back();
        cout << "---------- end ------------" << endl;
    }

    for (int i = 0; i < deq.size(); ++i) {
        printf("Address of object deq[%d]: 0x%llx\n", i, &deq[i]);
    }

    return 0;
}