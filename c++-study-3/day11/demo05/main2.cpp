/**
 * bind2nd和bind2nd的底层实现原理
 */

#include <iostream>
#include <vector>
#include <algorithm>

// 模拟实现 bind2nd 的功能

using namespace std;

// 函数对象（一元函数对象）
template<typename Compare, typename T>
class _my_bind2nd {

public:
    // 构造函数，比如：my_bind2nd(less<int>(), 5)
    _my_bind2nd(Compare comp, const T &second) : _comp(comp), _second(second) {

    }

    bool operator()(const T &first) {
        // 底层调用的仍然是二元（两个参数）函数对象
        return _comp(first, _second);
    }

private:
    Compare _comp;
    T _second;

};

// 绑定器（模拟 bind2nd 的实现）
// 绑定二元（两个参数）函数对象的第二个参数，生成一个新的一元函数对象，该函数对象接收原函数的第一个参数作为输入
template<typename Compare, typename T>
_my_bind2nd<Compare, T> my_bind2nd(Compare comp, const T &second) {
    return _my_bind2nd<Compare, T>(comp, second);
}

// 函数模板
template<typename Iterator, typename Compare>
Iterator my_find_if(Iterator first, Iterator last, Compare comp) {
    for (; first != last; ++first) {
        if (comp(*first)) {
            return first;
        }
    }
    return last;
}

int main() {
    vector<int> vec = {9, 6, 2, 4, 1};

    // 查找第一个小于 5 的元素

    // 使用 my_bind2nd 绑定 less 的第二个参数，使其始终为 5，让 less(x, 5) 变成一元函数对象，等价于 f(x) = (x < 5)
    vector<int>::iterator it = my_find_if(vec.begin(), vec.end(), my_bind2nd(less<int>(), 5));

    if (it != vec.end()) {
        cout << "找到小于 5 的第一个元素：" << *it << endl;
    } else {
        cout << "未找到符合条件的元素" << endl;
    }

    return 0;
}
