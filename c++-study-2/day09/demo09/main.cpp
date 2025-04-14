/*
 * 1. pair 对组的使用
*/

#include <iostream>

using namespace std;

int main() {

    // 第一种创建方式
    pair<string, int> p(string("Tom"), 18);
    cout << "name: " << p.first << ", age: " << p.second << endl;

    // 第二种创建方式
    pair<string, int> p2 = make_pair("Peter", 20);
    cout << "name: " << p2.first << ", age: " << p2.second << endl;

    return 0;
}
