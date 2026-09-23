/**
 * 迭代器的概念和分类
 *
 * (b) 迭代器的类型
 */

#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <typeinfo>
#include <vector>

// 重载函数
void _display_category(std::random_access_iterator_tag tag) {
    std::cout << "random_access_iterator_tag" << std::endl;
}

void _display_category(std::bidirectional_iterator_tag tag) {
    std::cout << "bidirectional_iterator_tag" << std::endl;
}

void _display_category(std::forward_iterator_tag tag) {
    std::cout << "forward_iterator_tag" << std::endl;
}

void _display_category(std::output_iterator_tag tag) {
    std::cout << "output_iterator_tag" << std::endl;
}

void _display_category(std::input_iterator_tag tag) {
    std::cout << "input_iterator_tag" << std::endl;
}

template <typename T>
void display_category(T ite) {
    std::cout << "----------begin----------" << std::endl;
    // 通过萃取获取 T 迭代器的类型
    typename std::iterator_traits<T>::iterator_category cagy;
    // 打印迭代器的类型
    _display_category(cagy);
    std::cout << "typeof(ite).name() = " << typeid(ite).name() << std::endl;
    std::cout << "-----------end-----------" << std::endl;
}

int main() {
    // std::array<int, 100>::iterator() 等写法是构造一个临时的迭代器对象，只为了把它的类型传给模板参数 T，并不真正遍历容器
    display_category(std::array<int, 100>::iterator());
    display_category(std::vector<int>::iterator());
    display_category(std::list<int>::iterator());
    display_category(std::map<int, int>::iterator());
    display_category(std::set<int>::iterator());
    return 0;
}