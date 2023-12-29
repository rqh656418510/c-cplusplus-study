/*
 * 1. 函数指针适配器的使用
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// 普通函数
void MyPrint(int v, int start) {
    cout << v + start << " ";
}

int main() {

    vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    // 0 ~ 9 加起始值，然后输出计算结果
    // ptr_fun 可以将函数指针适配为函数对象
    int num = 100;
    for_each(v.begin(), v.end(), bind2nd(ptr_fun(MyPrint), 100));

    return 0;
}
