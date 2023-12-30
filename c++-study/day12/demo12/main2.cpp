/*
 * 1. 取反适配器的使用
 *
 * 第一步：取反，如 not1 或者 not2，目的是将一个将函数对象的值翻转
 * 第二步：函数对象继承自 unary_function<参数类型, 返回值类型>
 * 第三步：operator() 加 const 修饰符
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// 函数对象（仿函数），继承自 unary_function
class GreaterThenFive : public unary_function<int, bool> {

public:

    bool operator()(int v) const {
        return v > 5;
    }

};

int main() {

    vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    // 查找第一个大于５的数字（第一种写法）
    vector<int>::iterator pos = find_if(v.begin(), v.end(), not1(GreaterThenFive()));
    if (pos != v.end()) {
        cout << "found first number greate then five is " << *pos << endl;
    } else {
        cout << "not found first number greate then five" << endl;
    }

    // 查找第一个大于５的数字（第二种写法）
    vector<int>::iterator pos2 = find_if(v.begin(), v.end(), not1(bind2nd(greater<int>(), 5)));
    if (pos2 != v.end()) {
        cout << "found first number greate then five is " << *pos2 << endl;
    } else {
        cout << "not found first number greate then five" << endl;
    }

    return 0;
}
