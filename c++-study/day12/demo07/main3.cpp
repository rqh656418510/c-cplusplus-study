/*
 * 1. list容器的反转与排序操作
*/

#include <iostream>
#include <list>

using namespace std;

void printList(list<int> &L) {
    for (list<int>::iterator it = L.begin(); it != L.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

bool myCompare(int v1, int v2) {
    return v1 > v2;
}

int main() {
    list<int> myList;
    myList.push_back(1);
    myList.push_back(3);
    myList.push_back(2);

    cout << "------ list 反转操作 ------" << endl;

    myList.reverse();
    printList(myList);

    cout << "------ list 排序操作 ------" << endl;

    // 排序（从小到大）
    myList.sort();
    printList(myList);

    // 排序（从大到小）
    myList.sort(myCompare);
    printList(myList);

    return 0;
}
