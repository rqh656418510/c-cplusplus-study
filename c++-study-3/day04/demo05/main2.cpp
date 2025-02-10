/**
 * 解决容器的迭代器失效问题
 */
#include <iostream>
#include <vector>

using namespace std;

void test01() {
    vector<int> v;
    for (int i = 0; i < 20; i++) {
        v.push_back(rand() % 100 + 1);
    }

    // 将容器中的所有偶数删除掉
    for (vector<int>::iterator it = v.begin(); it != v.end();) {
        if (*it % 2 == 0) {
            // 更新迭代器
            it = v.erase(it);
        } else {
            ++it;
        }
    }

}

void test02() {
    vector<int> v;
    for (int i = 0; i < 20; i++) {
        v.push_back(rand() % 100 + 1);
    }

    // 给容器中所有的偶数前面添加一个小于该偶数的数字
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if (*it % 2 == 0) {
            // 更新迭代器
            it = v.insert(it, *it - 1);
            ++it;
        }
    }
}

int main() {
    srand(time(nullptr));

    test01();
    test02();

    return 0;
}