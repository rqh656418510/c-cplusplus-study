/*
 * 1. vector容器的构造与赋值
*/

#include <iostream>
#include<vector>

using namespace std;

void printVector(vector<int> &v) {
    // 遍历容器
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    cout << "------ vector 构造函数 ------" << endl;

    // 默认构造函数
    vector<int> v1;

    // 有参构造函数，将 v[begin(), end()] 区间中的元素拷贝给本身
    vector<int> v2(arr, arr + sizeof(arr) / sizeof(int));
    printVector(v2);

    // 有参构造函数，将 v[begin(), end()] 区间中的元素拷贝给本身
    vector<int> v3(v2.begin(), v2.end());
    printVector(v3);

    // 有参构造函数，将 n 个元素拷贝给本身
    vector<int> v4(5, 10);
    printVector(v4);

    // 拷贝构造函数
    vector<int> v5 = v4;
    printVector(v5);

    cout << "------ vector 赋值操作 ------" << endl;

    // 赋值操作，将 v[begin(), end()] 区间中的元素拷贝给本身
    vector<int> v6;
    v6.assign(v5.begin(), v5.end());
    printVector(v6);

    // 赋值操作，将 n 个元素拷贝给本身
    vector<int> v7;
    v7.assign(5, 8);
    printVector(v7);

    // 赋值操作，重载等号操作符
    vector<int> v8;
    v8 = v6;
    printVector(v8);

    // 赋值操作，将其他容器与本身的元素互换，利用 swap() 可以收缩空间
    v8.swap(v7);
    printVector(v8);

    // 初始化匿名对象
    vector<int>(v9);
    v9.assign(5, 7);
    printVector(v9);

    return 0;
}