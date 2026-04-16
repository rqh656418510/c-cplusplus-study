#ifndef MYCLASS_H
#define MYCLASS_H

#include <iostream>

using namespace std;

// 类模板
template <typename T>
class MyClass {
public:
    void print(T value);
};

// 声明：显式实例化（告诉编译器这个实例在别处已经生成，当前翻译单元不要再实例化）
extern template class MyClass<int>;

#endif