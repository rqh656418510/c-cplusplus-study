/*
 * 1. deque容器的构造与赋值
*/

#include <iostream>
#include <deque>

using namespace std;

void printDeque(const deque<int> &d) {
    // 遍历容器
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    cout << "------ deque 构造函数 ------" << endl;

    // 默认构造函数
    deque<int> d1;

    // 有参构造函数，将 n 个 elem 元素拷贝给本身
    deque<int> d2(5, 10);
    printDeque(d2);

    // 有参构造函数，将 d[begin(), end()] 区间中的元素拷贝给本身
    deque<int> d3(d2.begin(), d2.end());
    printDeque(d3);

    // 拷贝构造函
    deque<int> d4 = d3;
    printDeque(d4);

    cout << "------ deque 赋值操作 ------" << endl;

    // 赋值操作，重载等号操作符
    deque<int> d5;
    d5 = d4;
    printDeque(d5);

    // 赋值操作，将 d[begin(), end()] 区间中的元素拷贝给本身
    deque<int> d6;
    d6.assign(d5.begin(), d5.end());
    printDeque(d6);

    // 赋值操作，将 n 个 elem 元素拷贝给本身
    deque<int> d7;
    d7.assign(5, 8);
    printDeque(d7);

    // 赋值操作，将其他容器与本身的元素互换
    d7.swap(d6);
    printDeque(d7);

    return 0;
}