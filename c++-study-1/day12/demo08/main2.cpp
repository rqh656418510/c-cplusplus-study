/*
 * 1. set / multiset 的常用操作
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

int main() {
    cout << "------ set 插入操作 ------" << endl;
    set<int> s1;
    s1.insert(3);
    s1.insert(9);
    s1.insert(5);
    s1.insert(8);
    printSet(s1);

    cout << "------ set 大小操作 ------" << endl;

    // 获取容器大小
    cout << "size = " << s1.size() << endl;

    // 判断容器是否为空
    cout << "isEmpty = " << (s1.empty() ? "true" : "false") << endl;

    cout << "------ set 查找操作 ------" << endl;

    // 查找键 Key 的元素个数，返回结果是 0 或者 1
    int count = s1.count(8);
    cout << "count = " << count << endl;

    // 查找键 Key 是否存在，若存在，则返回该键的元素的迭代器，若不存在，则返回 set.end() 迭代器
    set<int>::iterator pos = s1.find(8);
    if (pos != s1.end()) {
        cout << "found value for " << *pos << endl;
    } else {
        cout << "not found value" << endl;
    }

    // 返回第一个 key >= keyElem 元素的迭代器，若不存在，则返回 set.end() 迭代器
    set<int>::iterator pos2 = s1.lower_bound(8);
    if (pos2 != s1.end()) {
        cout << "found lower_bound(8) result is " << *pos2 << endl;
    }
    else {
        cout << "note found lower_bound(8) result" << endl;
    }

    // 返回第一个 key > keyElem 元素的迭代器，若不存在，则返回 set.end() 迭代器
    set<int>::iterator pos3 = s1.upper_bound(8);
    if (pos3 != s1.end()) {
        cout << "found upper_bound(8) result is " << *pos3 << endl;
    }
    else {
        cout << "note found upper_bound(8) result" << endl;
    }

    // 返回容器中 key 与 keyElem 相等的上下限的两个迭代器(即上限是 lower_bound，下限是 upper_bound)，若不存在，则返回 set.end() 迭代器
    pair<set<int>::iterator, set<int>::iterator> result = s1.equal_range(8);
    // 获取第一个结果值
    if (result.first != s1.end()) {
        cout << "found equal_range(8) first result is " << *result.first << endl;
    }
    else {
        cout << "note found equal_range(8) first result" << endl;
    }
    // 获取第二个结果值
    if (result.second != s1.end()) {
        cout << "found equal_range(8) second result is " << *result.second << endl;
    }
    else {
        cout << "note found equal_range(8) second result" << endl;
    }

    cout << "------ set 删除操作 ------" << endl;

    // 删除迭代器所指的元素，返回下一个元素的迭代器
    s1.erase(s1.begin());
    printSet(s1);

    // 删除容器中值为 elem 的元素
    s1.erase(5);
    printSet(s1);

    cout << "------ set 清空操作 ------" << endl;

    s1.clear();
    printSet(s1);

    return 0;
}
