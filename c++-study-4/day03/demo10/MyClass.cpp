#include "MyClass.h"

// 成员函数定义
template <typename T>
void MyClass<T>::print(T value) {
    cout << "value: " << value << endl;
}

// 定义：显式实例化（告诉编译器在当前 .cpp 源文件中真正生成代码）
template class MyClass<int>;
