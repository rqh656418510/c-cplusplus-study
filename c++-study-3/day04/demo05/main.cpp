/**
 * 什么是容器的迭代器失效问题
 */
#include <iostream>
#include <vector>

using namespace std;

void test01() {
    vector<int> v;
    for (int i = 0; i < 20; i++) {
        v.push_back(rand() % 100 + 1);
    }

    // 将容器中的所有偶数删除掉
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if (*it % 2 == 0) {
            // 迭代器失效的问题：第一次调用 erase() 函数以后，迭代器 it 就已经失效了
            // 当容器调用 erase() 函数后，当前删除位置到容器尾元素的所有的选代器将全部失效，但是首元素到当前删除位置的所有的迭代器依旧是生效的
            v.erase(it);
        }
    }
}

void test02() {
    vector<int> v;
    for (int i = 0; i < 20; i++) {
        v.push_back(rand() % 100 + 1);
    }

    // 给容器中所有的偶数前面添加一个小于该偶数的数字
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if (*it % 2 == 0) {
            // 迭代器失效的问题：第一次调用 insert() 函数以后，迭代器 it 就已经失效了
            // 当容器调用 insert() 函数后，当前插入位置到容器尾元素的所有的选代器将全部失效，但是首元素到当前插入位置的所有的迭代器依旧是生效的
            // 一旦 insert() 函数的插入操作引起扩容，那么原来容器从首元素到尾元素的所有的选代器将全部失效
            v.insert(it, *it - 1);
        }
    }
}

int main() {
    srand(time(nullptr));

    // test01();
    test02();

    return 0;
}