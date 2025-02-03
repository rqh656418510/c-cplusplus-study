/**
 * 迭代器iterator
 */

#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

int main() {
    // 设置随机种子
    srand(time(nullptr));

    vector<int> v1;

    for (int i=0; i< 10; i++) {
        v1.push_back(rand() % 100  + 1);
    }

    // 正向迭代器
    for (vector<int>::iterator it = v1.begin(); it!= v1.end(); ++it){
        if (*it % 2 ==0 ){
            // 可以赋值
            *it = *it + 1;
        }
        cout << *it << " ";
    }
    cout << endl;

    // 常量的正向迭代器
    for (vector<int>::const_iterator it = v1.begin(); it!= v1.end(); ++it){
        if (*it % 2 ==0 ){
            // 错误写法，不可以赋值
            // *it = *it + 1;
        }
        cout << *it << " ";
    }
    cout << endl;

    // 反向迭代器
    for (vector<int>::reverse_iterator it = v1.rbegin(); it!= v1.rend(); ++it){
        if (*it % 2 ==0 ){
            // 可以赋值
            *it = *it + 1;
        }
        cout << *it << " ";
    }
    cout << endl;

    // 常量的反向迭代器
    for (vector<int>::const_reverse_iterator it = v1.rbegin(); it!= v1.rend(); ++it){
        if (*it % 2 ==0 ){
            // 错误写法，不可以赋值
            // *it = *it + 1;
        }
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
