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
    printList(myList1);

    // 往容器的头部插入元素
    myList1.push_front(300);
    myList1.push_front(200);
    myList1.push_front(100);
    printList(myList1);

    // 往 pos 位置插入 elem 数据的拷贝，返回新数据的位置
    myList1.insert(myList1.begin(), 400);
    printList(myList1);

    // 往 pos 位置插入 n 个 elem 数据，无返回值
    myList1.insert(myList1.begin(), 2, 500);
    printList(myList1);

    // 往 pos 位置插入 [begin, end) 区间的数据，无返回值
    list<int> myList2;
    myList2.push_back(1);
    myList2.push_back(2);
    myList2.push_back(3);
    myList1.insert(myList1.begin(), myList2.begin(), myList2.end());
    printList(myList1);

    cout << "------ list 删除操作 ------" << endl;

    // 删除容器头部的数据
    myList1.pop_front();
    printList(myList1);

    // 删除容器尾部的数据
    myList1.pop_back();
    printList(myList1);

    // 删除 pos 位置的数据，返回下一个数据的位置
    myList1.erase(myList1.begin());
    printList(myList1);

    // 删除容器中所有与 elem 值匹配的元素
    myList1.remove(100);
    printList(myList1);

    cout << "------ list 读取操作 ------" << endl;

    // 获取第一个元素
    cout << myList1.front() << endl;

    // 获取最后一个元素
    cout << myList1.back() << endl;

    cout << "------ list 清空操作 ------" << endl;

    list<int> myList3;
    myList3.push_back(10);
    myList3.push_back(10);
    myList3.clear();
    printList(myList3);

    cout << "------ list 大小操作 ------" << endl;

    // 返回容器中元素的个数
    cout << "size = " << myList1.size() << endl;

    // 判断容器是否为空
    bool isEmpty = myList1.empty();
    cout << "isEmpty = " << (isEmpty ? "true" : "false") << endl;

    // 重新指定容器的长度 num，若容器变长，则以默认值填充新位置，若容器变短，则末尾超出容器长度的元素会被删除
    myList1.resize(6);
    cout << "size = " << myList1.size() << endl;

    // 重新指定容器的长度 num，若容器变长，则以 elem 值填充新位置，若容器变短，则末尾超出容器长度的元素会被删除
    myList1.resize(9, 11);
    printList(myList1);
    cout << "size = " << myList1.size() << endl;

    cout << "------ list 逆向遍历操作 ------" << endl;

    list<int> myList11;
    myList11.push_back(1);
    myList11.push_back(2);
    myList11.push_back(3);
    reversePrintList(myList11);

    return 0;
}
