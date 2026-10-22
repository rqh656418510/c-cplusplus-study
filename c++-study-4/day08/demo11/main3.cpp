/**
 * 萃取(traits)技术概念、范例等
 *
 * (c) 迭代器萃取可以配合函数重载，根据迭代器类型选择不同的算法实现
 */

#include <iostream>
#include <iterator>
#include <list>
#include <vector>

using namespace std;

// 随机访问迭代器：通过相减直接计算距离
template <typename Iter>
typename iterator_traits<Iter>::difference_type myDistance(Iter first, Iter last, random_access_iterator_tag) {
    cout << "Using random access iterator algorithm" << endl;
    return last - first;
}

// 其他迭代器：通过逐步遍历计算距离
template <typename Iter, typename Category>
typename iterator_traits<Iter>::difference_type myDistance(Iter first, Iter last, Category) {
    cout << "Using step-by-step traversal algorithm" << endl;
    typename iterator_traits<Iter>::difference_type n = 0;
    while (first != last) {
        ++first;
        ++n;
    }
    return n;
}

// 利用迭代器萃取获取迭代器类别
template <typename Iter>
typename iterator_traits<Iter>::difference_type myDistance(Iter first, Iter last) {
    using Category = typename iterator_traits<Iter>::iterator_category;
    return myDistance(first, last, Category{});
}

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    list<int> lst = {1, 2, 3, 4, 5};

    cout << "Vector distance: " << myDistance(vec.begin(), vec.end()) << endl;
    cout << "List distance: " << myDistance(lst.begin(), lst.end()) << endl;

    return 0;
}