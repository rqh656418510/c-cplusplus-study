/**
 * bind1st和bind2nd的底层实现原理
 */

#include <iostream>
#include <vector>
#include <algorithm>

// 模拟实现 bind1st 的功能

using namespace std;

// 函数对象（一元函数对象）
template<typename Compare, typename T>
class _my_bind1st {

public:
    // 构造函数，比如：my_bind1st(greater<int>(), 5)
    _my_bind1st(Compare comp, const T &first) : _comp(comp), _first(first) {

    }

    bool operator()(const T &second) {
        // 底层调用的仍然是二元（两个参数）函数对象
        return _comp(_first, second);
    }

private:
    Compare _comp;
    T _first;

};

// 绑定器（模拟 bind1st 的实现）
// 绑定二元（两个参数）函数对象的第一个参数，生成一个新的一元函数对象，该函数对象接收原函数的第二个参数作为输入
template<typename Compare, typename T>
_my_bind1st<Compare, T> my_bind1st(Compare comp, const T &first) {
    return _my_bind1st<Compare, T>(comp, first);
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

    // 使用 my_bind1st 绑定 greater 的第一个参数，使其始终为 5，让 greater(5, x) 变成一元函数对象，等价于 f(x) = (5 > x)
    vector<int>::iterator it = my_find_if(vec.begin(), vec.end(), my_bind1st(greater<int>(), 5));

    if (it != vec.end()) {
        cout << "找到小于 5 的第一个元素：" << *it << endl;
    } else {
        cout << "未找到符合条件的元素" << endl;
    }

    return 0;
}
