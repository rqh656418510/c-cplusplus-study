/**
 * 容器的说明和简单应用例续
 *
 * (g) unordered_set 使用
 */

#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    unordered_set<int> mySet;
    cout << "bucket count: " << mySet.bucket_count() << endl;
    cout << "bucket size: " << mySet.bucket_size(0) << endl;
    cout << "size: " << mySet.size() << endl;

    for (int i = 0; i < 5; ++i) {
        mySet.insert(i);
    }

    cout << "bucket count: " << mySet.bucket_count() << endl;
    cout << "bucket size: " << mySet.bucket_size(0) << endl;
    cout << "size: " << mySet.size() << endl;

    for (int i = 0; i < mySet.bucket_count(); ++i) {
        cout << "第 " << i + 1 << " 个 bucket 有 " << mySet.bucket_size(i) << " 元素" << endl;
    }

    const auto iter = mySet.find(3);
    if (iter != mySet.end()) {
        cout << "found number " << *iter << endl;
    } else {
        cout << "not found number 3" << endl;
    }

    return 0;
}