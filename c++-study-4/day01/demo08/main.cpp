/**
 * 迭代器精彩演绎，失效分析及弥补、实战
 */

#include <iostream>
#include <vector>

using namespace std;

// vector 的迭代器
void test0() {
    vector<string> v1 = {"a", "b", "c", "d", "e"};

    // 普通正向迭代器
    for (vector<string>::iterator it = v1.begin(); it != v1.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 只读正向迭代器
    for (vector<string>::const_iterator it = v1.cbegin(); it != v1.cend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 普通反向迭代器
    for (vector<string>::reverse_iterator it = v1.rbegin(); it != v1.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 只读反向迭代器
    for (vector<string>::const_reverse_iterator it = v1.crbegin(); it != v1.crend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

// vector 迭代器支持的操作
void test1() {
    vector<string> v1 = {"a", "b", "c", "d", "e"};
    vector<string>::iterator it = v1.begin();

    // 迭代器支持 * 操作
    cout << *it << endl;

    // 迭代器支持 [] 操作
    cout << it[1] << endl;

    // 迭代器支持 ++ 操作
    ++it;
    cout << *it << endl;

    // 迭代器支持 -- 操作
    --it;
    cout << *it << endl;
}

int main() {
    test0();
    test1();
    return 0;
}