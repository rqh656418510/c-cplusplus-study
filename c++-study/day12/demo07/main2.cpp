/*
 * 1. list容器的常用操作
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

void reversePrintList(list<int> &L) {
    // 逆向遍历
    for (list<int>::reverse_iterator it = L.rbegin(); it != L.rend(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    cout << "------ list 插入操作 ------" << endl;

    list<int> myList1;

    // 往容器的尾部插入元素
    myList1.push_back(10);
    myList1.push_back(20);
    myList1.push_back(30);

    // 往容器的头部插入元素
    myList1.push_front(300);
    myList1.push_front(200);
    myList1.push_front(100);
    printList(myList1);

    cout << "------ list 删除操作 ------" << endl;

    // 删除容器头部的数据
    myList1.pop_front();

    // 删除容器尾部的数据
    myList1.pop_back();
    printList(myList1);

    cout << "------ 逆向遍历操作 ------" << endl;

    list<int> myList2;
    myList2.push_back(1);
    myList2.push_back(2);
    myList2.push_back(3);
    reversePrintList(myList2);

    return 0;
}
