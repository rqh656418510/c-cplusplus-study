/*
 * 可变参模板续、模板模板参数
 *
 * (c) 模板模板参数
 */

#include <iostream>
#include <list>
#include <vector>

using namespace std;

// 定义类模板（使用了模板模板参数）
template <typename T, template <typename> class Container>
class MyClass {
public:
    MyClass() {
        for (int i = 0; i < 10; ++i) {
            // 插入数据
            m_c.push_back(i);
        }
    }

public:
    Container<T> m_c;  // Container 作为一个类模板来使用，T 作为一个类型来使用
};

// 通过 using 定义别名模板
template <typename T>
using MyList = list<T, allocator<T>>;

// 通过 using 定义别名模板
template <typename T>
using MyVector = vector<T, allocator<T>>;

int main() {
    MyClass<int, MyList> m1;
    MyClass<int, MyVector> m2;
    return 0;
}