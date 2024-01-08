/*
 * 1. 常用的查找算法 - count
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> v;

    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(5);
    v.push_back(6);

    int total = count(v.begin(), v.end(), 5);
    cout << "total: " << total << endl;

    return 0;
}
