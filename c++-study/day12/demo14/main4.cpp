/*
 * 1. 常用的查找算法 - binary_search
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> v;

    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    bool result = binary_search(v.begin(), v.end(), 5);
    if (result) {
        cout << "find number for 5" << endl;
    } else {
        cout << "not found number for 5" << endl;
    }

    return 0;
}
