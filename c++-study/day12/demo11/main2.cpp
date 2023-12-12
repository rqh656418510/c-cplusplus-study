/*
 * 1. map / multimap 的排序操作
*/

#include <iostream>
#include <map>

using namespace std;

// 仿函数
class myCompare {

public:
    // 重载
    bool operator()(const int &v1, const int &v2) {
        // 排序规则
        return v1 > v2;
    }
};

void printMap(map<int, int, myCompare> &m) {
    // 遍历容器
    for (map<int, int, myCompare>::iterator it = m.begin(); it != m.end(); it++) {
        cout << "key = " << it->first << ", value = " << it->second << endl;
    }
}

int main() {
    // 使用仿函数，让 map 容器按照 key 进行倒序排序（从大到小）
    map<int, int, myCompare> m1;
    m1.insert(make_pair(1, 8));
    m1.insert(make_pair(7, 2));
    m1.insert(make_pair(4, 10));
    m1.insert(make_pair(9, 5));
    printMap(m1);
    return 0;
}
