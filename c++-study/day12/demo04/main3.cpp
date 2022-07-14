/*
 * 1. deque容器的排序操作
*/

#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

void printDeque(const deque<int> &d) {
    // 遍历容器
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

void asc() {
    deque<int> d1;
    d1.push_back(3);
    d1.push_back(11);
    d1.push_back(8);
    d1.push_back(6);
    d1.push_back(21);

    cout << "升序排序前：" << endl;
    printDeque(d1);

    // 升序排序，默认从小到大排序
    sort(d1.begin(), d1.end());

    cout << "升序排序后：" << endl;
    printDeque(d1);
}

void desc() {
    deque<int> d1;
    d1.push_back(3);
    d1.push_back(11);
    d1.push_back(8);
    d1.push_back(6);
    d1.push_back(21);

    cout << "降序排序前：" << endl;
    printDeque(d1);

    // 降序排序，默认从大到小排序
    sort(d1.rbegin(), d1.rend());

    cout << "降序排序后：" << endl;
    printDeque(d1);
}

int main() {
    asc();  // 升序排序
    cout << endl;
    desc(); // 降序排序后
    return 0;
}