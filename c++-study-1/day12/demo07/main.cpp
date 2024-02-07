/*
 * 1. list容器的构造与赋值
*/

#include <iostream>
#include <list>

using namespace std;

void printList(list<int> &L) {
    // 遍历容器
    for (list<int>::iterator it = L.begin(); it != L.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {

    cout << "------ list 构造函数 ------" << endl;

    // 默认构造函数
    list<int> myList1;

    // 有参构造函数，将 n 个 elem 元素拷贝给本身
    list<int> myList2(5, 10);
    printList(myList2);

    // 有参构造函数，将 [begin, end) 区间中的元素拷贝给本身
    list<int> myList3(myList2.begin(), myList2.end());
    printList(myList3);

    // 拷贝构造函数
    list<int> myList4 = myList2;
    printList(myList4);

    cout << "------ list 赋值操作 ------" << endl;

    // 赋值操作，将 [begin, end) 区间中的元素拷贝给本身
    list<int> myList5;
    myList5.assign(myList2.begin(), myList2.end());
    printList(myList5);

    // 赋值操作，将 n 个 elem 元素拷贝给本身
    list<int> myList6;
    myList6.assign(5, 8);
    printList(myList6);

    // 赋值操作，重载等号操作符
    list<int> myList7;
    myList7 = myList2;
    printList(myList7);

    // 赋值操作，将其他容器与本身的元素互换
    myList6.swap(myList7);
    printList(myList6);
    printList(myList7);

    return 0;
}
