/*
 * 1. 常用的遍历算法 - for_each
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

// 普通函数
void myPrint(int v) {
    cout << v << " ";
}

// 函数对象
class MyPrint {

public:
    void operator()(const int &v) {
        cout << v << " ";
    }

};

// 函数对象
class MyPrint2 {

public:
    void operator()(const int &v) {
        cout << v << " ";
        count++;
    }

    int count;

};

// 函数对象
class MyPrint3 : public binary_function<int, int, void> {

public:
    void operator()(int v, int start) const {
        cout << v + start << " ";
    }

};

int main() {

    vector<int> v;

    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    // for_each 使用普通函数
    for_each(v.begin(), v.end(), myPrint);

    cout << endl;

    // for_each 使用匿名函数
    for_each(v.begin(), v.end(), [](int value) { cout << value << " "; });

    cout << endl;

    // for_each 使用函数对象
    for_each(v.begin(), v.end(), MyPrint());

    cout << endl;

    // for_each 拥有返回值（基于函数对象），可用于保存内部记录
    MyPrint2 myPrint2 = for_each(v.begin(), v.end(), MyPrint2());
    cout << endl << "count = " << myPrint2.count << endl;

    // for_each 可以绑定参数进行输出（基于函数适配器）
    for_each(v.begin(), v.end(), bind2nd(MyPrint3(), 100));

    return 0;
}
