/**
 * 容器的说明和简单应用例续
 *
 * (f) map 使用
 */

#include <iostream>
#include <map>

using namespace std;

int main() {
    map<int, string> myMap;

    myMap.insert(make_pair(1, "Tom"));
    myMap.insert(make_pair(2, "Jim"));
    myMap.insert(pair<int, string>(3, "Peter"));

    // 当用 insert 插入已存在的 Key，会插入失败，原值不变
    myMap.insert(pair<int, string>(1, "David"));

    auto iter = myMap.find(1);
    if (iter != myMap.end()) {
        cout << "key: " << iter->first << ", value: " << iter->second << endl;
    }

    return 0;
}