/**
 * 泛型算法和绑定器
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

void test01() {
    cout << "============ test01() ============" << endl;

    int arr[] = {12, 23, 7, 11, 39, 25, 45, 48, 58};
    vector<int> v1(arr, arr + sizeof(arr) / sizeof(arr[0]));

    for (int val : v1) {
        cout << val << " ";
    }
    cout << endl;

    // 排序算法（默认从小到大排序）
    sort(v1.begin(), v1.end(), greater<int>());

    for (int val : v1) {
        cout << val << " ";
    }
    cout << endl;

    // 二分查找算法（适用于有序容器）
    if (binary_search(v1.begin(), v1.end(), 25)) {
        cout << "found number 25" << endl;
    } else {
        cout << "not found 25" << endl;
    }

    // 查找算法
    vector<int>::iterator it1 = find(v1.begin(), v1.end(), 48);
    if (it1 != v1.end()) {
        cout << "found number 48" << endl;
    } else {
        cout << "not found 48" << endl;
    }
}

void test02() {
    cout << "============ test02() ============" << endl;

    int arr[] = {22, 33, 8, 21, 59, 35, 55, 63, 70};
    vector<int> v1(arr, arr + sizeof(arr) / sizeof(arr[0]));

    // 排序算法（默认从小到大排序）
    sort(v1.begin(), v1.end());

    for (int val : v1) {
        cout << val << " ";
    }
    cout << endl;

    // 条件查找算法，将 48 按顺序插入到 vector 容器中

    // 使用绑定器（已过时的写法）
    vector<int>::iterator it2 = find_if(v1.begin(), v1.end(), bind1st(less<int>(), 48));

    // 使用绑定器（现代 C++ 的写法）
    // vector<int>::iterator it2 = find_if(v1.begin(), v1.end(), bind(greater<int>(), placeholders::_1, 48));

    // 使用绑定器（Lambda 表达式的写法）
    // vector<int>::iterator it2 = find_if(v1.begin(), v1.end(), [](int val) -> bool { return val > 48; });

    v1.insert(it2, 48);

    for (int val : v1) {
        cout << val << " ";
    }
    cout << endl;
}

void test03() {
    cout << "============ test03() ============" << endl;

    vector<int> v1;
    for (int i = 0; i < 10; i++) {
        v1.push_back(rand() % 100 + 1);
    }

    for (int val : v1) {
        cout << val << " ";
    }
    cout << endl;

    // 遍历算法
    for_each(v1.begin(), v1.end(), [](int val) -> void {
        // 打印所有偶数
        if (val % 2 == 0) {
            cout << val << " ";
        }
    });
    cout << endl;

}

int main() {
    // 设置随机种子
    srand(time(nullptr));
    test01();
    test02();
    test03();
    return 0;
}
