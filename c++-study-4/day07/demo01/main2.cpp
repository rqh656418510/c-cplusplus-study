/**
 * STL总述、发展史、组成，数据结构谈
 *
 * (b) vector（向量）使用
 */

#include <iostream>
#include <vector>

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
    int m_i;
};

int main() {
    vector<MyClass> vec;

for (int i = 0; i < 3; ++i) {
        cout << "---------- begin ----------" << endl;
        cout << "Container size before insertion = " << vec.size() << endl;
        cout << "Container capacity before insertion = " << vec.capacity() << endl;
        vec.push_back(MyClass());
        cout << "Container size after insertion = " << vec.size() << endl;
        cout << "Container capacity after insertion = " << vec.capacity() << endl;
        cout << "---------- end ------------" << endl;
    }

    return 0;
}