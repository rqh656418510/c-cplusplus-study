/**
 * 理解容器空间配置器allocator的重要性
 */

#include <iostream>
#include <cstring>

using namespace std;

// 类模板
template<typename T>
// 向量容器
class MyVector {

public:
    // 构造函数（需要将内存开辟和对象构造分开处理）
    MyVector(int size = 10) {
        _first = new T[size];
        _last = _first;
        _end = _first + size;
    }

    // 析构函数（先析构容器内的有效元素，然后再释放 _first 指针执行的堆内存）
    ~MyVector() {
        //
        if (_first != nullptr) {
            delete[] _first;
            _first = _last = _end = nullptr;
        }
    }

    // 拷贝构造函数
    MyVector(const MyVector<T> &v) {
        // 容器的总大小
        int size = v._end - v._first;
        // 有效元素的个数
        int length = v._last - v._first;
        // 深拷贝
        _first = new T[size];
        for (int i = 0; i < length; i++) {
            _first[i] = v._first[i];
        }
        _last = _first + length;
        _end = _first + size;
    }

    // 赋值运算符重载
    MyVector<T> &operator=(const MyVector<T> &v) {
        if (this == v) {
            return *this;
        }

        // 释放原来的内存空间
        if (_first != nullptr) {
            delete[] _first;
        }

        // 容器的总大小
        int size = v._end - v._first;
        // 有效元素的个数
        int length = v._last - v._first;
        // 深拷贝
        _first = new T[size];
        for (int i = 0; i < length; i++) {
            _first[i] = v._first[i];
        }
        _last = _first + length;
        _end = _first + size;
    }

    // 往容器尾部添加元素
    void push_back(const T &val) {
        if (full()) {
            resize();
        }
        *_last++ = val;
    }

    // 从容器尾部删除元素（需要将对象的析构和内存释放分开处理）
    void pop_back() {
        if (!empty()) {
            --_last;
        }
    }

    // 返回容器尾部的元素
    T back() const {
        if (empty()) {
            throw "MyVector is empty!";
        }
        return *(_last - 1);
    }

    // 容器是否满了
    bool full() const {
        return _last == _end;
    }

    // 容器是否为空
    bool empty() const {
        return _first == _last;
    }

    // 返回有效元素的个数
    int size() {
        return _last - _first;
    }

private:
    T *_first;  // 指向数组起始的位置
    T *_last;   // 指向数组中有效元素的后继位置
    T *_end;    // 指向数组空间的后继位置

    // 扩容操作
    void resize() {
        int size = _end - _first;
        T *_ptemp = new T[size * 2];

        for (int i = 0; i < size; i++) {
            _ptemp[i] = _first[i];
        }

        // 释放原来的内存空间
        delete[] _first;

        _first = _ptemp;
        _last = _first + size;
        _end = _first + size * 2;
    }
};

class Person {

public:
    Person() {
        cout << "call Person()" << endl;
    }

    ~Person() {
        cout << "call ~Person()" << endl;
    }
};

void test01() {
    // 设置随机数种子
    srand(time(nullptr));

    MyVector<int> v;
    for (int i = 0; i < 20; i++) {
        int val = random() % 100;
        v.push_back(val);
        cout << val << " ";
    }
    cout << endl;

    cout << "size: " << v.size() << endl;
    cout << "full: " << (v.full() ? "true" : " false") << endl;
    cout << "empty: " << (v.empty() ? "true" : " false") << endl;

    while (!v.empty()) {
        cout << v.back() << " ";
        v.pop_back();
    }
}

void test02() {
    Person p1, p2, p3;
    cout << "===============" << endl;
    MyVector<Person> v;
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    cout << "===============" << endl;
    v.pop_back();
    cout << "===============" << endl;
}

int main() {
    // test01();
    test02();
    return 0;
}
