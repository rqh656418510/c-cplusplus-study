/*
 * 1. set / multiset 的常用操作
*/

#include <iostream>
#include <set>

using namespace std;

// 仿函数
class myCustomCompare {
public:
    // 重载
    bool operator()(int v1, int v2) {
        // 排序规则
        return v1 > v2;
    }
};

void printSet(set<int> &s) {
    // 遍历容器
    for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

void printGreaterSet(set<int, greater<int>> &s) {
    // 遍历容器
    for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

void printCustomCompareSet(set<int, myCustomCompare> &s) {
    // 遍历容器
    for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    cout << "------ set 容器不允许插入重复的元素 ------" << endl;

    set<int> s1;

    pair<set<int>::iterator, bool> result = s1.insert(10);
    if (result.second) {
        cout << "insert success" << endl;
    } else {
        cout << "insert failed" << endl;
    }

    result = s1.insert(10);
    if (result.second) {
        cout << "insert success" << endl;
    } else {
        cout << "insert failed" << endl;
    }

    printSet(s1);

    cout << "------ set 容器对元素进行排序操作 ------" << endl;

    // 容器按升序方式排列元素（从小到大）
    set<int, less<int>> s2;
    s2.insert(5);
    s2.insert(1);
    s2.insert(7);
    s2.insert(3);
    s2.insert(9);
    printSet(s2);

    // 容器按降序方式排列元素（从大到小）
    set<int, greater<int>> s3;
    s3.insert(5);
    s3.insert(1);
    s3.insert(7);
    s3.insert(3);
    s3.insert(9);
    printGreaterSet(s3);

    // 按照自定义的排序方式排列元素
    set<int, myCustomCompare> s4;
    s4.insert(5);
    s4.insert(1);
    s4.insert(7);
    s4.insert(3);
    s4.insert(9);
    s4.insert(9);
    printCustomCompareSet(s4);

    return 0;
}
