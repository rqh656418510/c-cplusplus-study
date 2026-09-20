/**
 * 容器的说明和简单应用例续
 *
 * (d) list 容器使用
 */

#include <iostream>
#include <list>

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
    list<MyClass> list;

    for (int i = 0; i < 3; ++i) {
        cout << "---------- begin ----------" << endl;
        list.push_back(MyClass());
        cout << "---------- end ------------" << endl;
    }

    int i = 1;
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        cout << "第 " << i << " 个对象的地址：" << &(*iter) << endl;
        ++i;
    }

    return 0;
}