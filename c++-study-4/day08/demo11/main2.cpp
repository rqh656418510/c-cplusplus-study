/**
 * 萃取(traits)技术概念、范例等
 *
 * (b) 迭代器萃取
 */

#include <iostream>
#include <iterator>
#include <list>
#include <typeinfo>
#include <vector>

using namespace std;

template <typename Iter>
void printIteratorInfo(Iter iter) {
    using Category = typename iterator_traits<Iter>::iterator_category;      // 获取迭代器的类别，如随机访问迭代器、双向迭代器
    using ValueType = typename iterator_traits<Iter>::value_type;            // 获取迭代器指向的元素类型
    using DifferenceType = typename iterator_traits<Iter>::difference_type;  // 获取两个迭代器之间距离的类型
    using Pointer = typename iterator_traits<Iter>::pointer;                 // 获取迭代器对应的指针类型
    using Reference = typename iterator_traits<Iter>::reference;             // 获取迭代器对应的引用类型

    cout << "Iterator Category: " << typeid(Category).name() << endl;
    cout << "Value Type: " << typeid(ValueType).name() << endl;
    cout << "Difference Type: " << typeid(DifferenceType).name() << endl;
    cout << "Pointer Type: " << typeid(Pointer).name() << endl;
    cout << "Reference Type: " << typeid(Reference).name() << endl;
}

int main() {
    vector<int> vec = {1, 2, 3};
    list<int> lst = {4, 5, 6};

    cout << "Vector Iterator Info:" << endl;
    printIteratorInfo(vec.begin());

    cout << "\nList Iterator Info:" << endl;
    printIteratorInfo(lst.begin());

    return 0;
}