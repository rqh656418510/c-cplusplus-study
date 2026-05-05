/**
 * 类模板概念，类模板定义、使用
 */

#include <iostream>

#include "MyVector.hpp"

using namespace std;

template <int C>
void show(MyVector<int, C>& v) {
    for (typename MyVector<int, C>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    MyVector<int, 5> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    show(v1);

    MyVector<int, 5> v2 = v1;
    show(v2);

    v2 = v1;
    show(v2);

    return 0;
}