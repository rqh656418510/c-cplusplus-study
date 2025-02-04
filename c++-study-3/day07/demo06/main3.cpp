/**
 * 函数对象
 *
 * <p> 函数对象的使用
 */

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

void test01() {
    cout << "============ test01() ============" << endl;

    // 使用函数对象，让优先级队列里的元素从小到大排序（默认从大到小排序）
    priority_queue<int, vector<int>, greater<int>> q1;
    for (int i = 0; i < 10; i++) {
        int val = rand() % 100 + 1;
        q1.push(val);
        cout << val << " ";
    }
    cout << endl;

    while (!q1.empty()) {
        cout << q1.top() << " ";
        q1.pop();
    }
    cout << endl;
}

void test02() {
    cout << "============ test02() ============" << endl;

    // 使用函数对象，让有序集合里的元素从大到小排序（默认从小到大排序）
    set<int, greater<int>> s1;
    for (int i = 0; i < 10; i++) {
        int val = rand() % 100 + 1;
        s1.insert(val);
        cout << val << " ";
    }
    cout << endl;

    for (set<int>::iterator it = s1.begin(); it != s1.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

}

int main() {
    // 设置随机种子
    srand(time(nullptr));

    test01();
    test02();
    return 0;
}
