/*
 * 1. set / multiset 的构造与赋值
*/

#include <iostream>
#include <set>

using namespace std;

void printSet(set<int> &s) {
    // 遍历容器
    for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

void printMultiSet(multiset<int> &s) {
    // 遍历容器
    for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {

    cout << "------ set 构造函数 ------" << endl;

    // 默认构造函数
    set<int> s1;

    // 关联式容器，默认按照 Key 从小到大排序
    s1.insert(5);
    s1.insert(2);
    s1.insert(9);
    s1.insert(4);
    s1.insert(3);
    printSet(s1);

    // 拷贝构造函数
    set<int> s2 = s1;
    printSet(s2);

    cout << "------ set 赋值操作 ------" << endl;

    // 赋值操作，重载等号操作符
    set<int> s3;
    s3 = s1;
    printSet(s3);

    // 赋值操作，将其他容器与本身的元素互换
    set<int> s4;
    s4.insert(10);
    s4.insert(30);
    s4.insert(20);
    s4.swap(s1);
    printSet(s1);
    printSet(s4);

    cout << "------ multiset 构造函数 ------" << endl;

    multiset<int> s5;

    // multiset 允许插入多个相同的元素
    s5.insert(5);
    s5.insert(2);
    s5.insert(2);
    s5.insert(3);
    s5.insert(3);
    printMultiSet(s5);

    // 拷贝构造函数
    multiset<int> s6 = s5;
    printMultiSet(s6);

    cout << "------ multiset 赋值操作 ------" << endl;

    // 赋值操作，重载等号操作符
    multiset<int> s7;
    s7 = s5;
    printMultiSet(s7);

    // 赋值操作，将其他容器与本身的元素互换
    multiset<int> s8;
    s8.insert(10);
    s8.insert(30);
    s8.insert(20);
    s8.swap(s5);
    printMultiSet(s5);
    printMultiSet(s8);

    return 0;
}