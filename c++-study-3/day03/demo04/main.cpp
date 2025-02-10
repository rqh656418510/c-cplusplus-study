/**
 * 理解容器空间配置器allocator的重要性
 */

#include <iostream>
#include <cstring>

using namespace std;

// 类模板
template<typename T>
// 空间配置器（负责内存开辟、内存释放、对象构造、对象析构）
struct MyAllocator {

    // 数组的内存开辟
    T *allocate(size_t size) {
        return (T *) malloc(sizeof(T) * size);
    }

    // 数组的内存释放
    void deallocate(void *p) {
        free(p);
    }

    // 对象构造
    void construct(T *p, const T &val) {
        // 在指定的内存上构造对象（定位 new）
        new (p)T(val);
    }

    // 对象析构
    void destroy(T *p) {
        // ~T() 代表了 T 类型对象的析构函数
        p->~T();
    }

};

// 类模板
template<typename T, typename Alloc = MyAllocator<T>>
// 向量容器
class MyVector {

public:
    // 构造函数
    MyVector(int size = 10) {
        // 开辟数组的内存空间
        _first = _allocator.allocate(size);
        _last = _first;
        _end = _first + size;
    }

    // 析构函数（先析构容器内的有效元素，然后再释放 _first 指针指向的堆内存）
    ~MyVector() {
        // 析构容器内的有效元素
        for (T *p = _first; p != _last; p++) {
            _allocator.destroy(p);
        }

        // 释放堆上的数组内存
        _allocator.deallocate(_first);
        _first = _last = _end = nullptr;
    }

    // 拷贝构造函数
    MyVector(const MyVector<T> &v) {
        // 容器的总大小
        int size = v._end - v._first;
        // 有效元素的个数
        int length = v._last - v._first;

        // 开辟数组的内存空间
        _first = _allocator.allocate(size);

        // 在指定的内存空间中构造对象
        for (int i = 0; i < length; i++) {
            _allocator.construct(_first + i, v._first[i]);
        }
        _last = _first + length;
        _end = _first + size;
    }

    // 赋值运算符重载
    MyVector<T> &operator=(const MyVector<T> &v) {
        if (this == v) {
            return *this;
        }

        // 析构容器内的有效元素
        for (T *p = _first; p != _last; p++) {
            _allocator.destroy(p);
        }

        // 释放堆上的数组内存
        _allocator.deallocate(_first);

        // 容器的总大小
        int size = v._end - v._first;
        // 有效元素的个数
        int length = v._last - v._first;

        // 开辟数组的内存空间
        _first = _allocator.allocate(size);

        // 在指定的内存空间中构造对象
        for (int i = 0; i < length; i++) {
            _allocator.construct(_first + i, v._first[i]);
        }
        _last = _first + length;
        _end = _first + size;

        return *this;
    }

    // 往容器尾部添加元素
    void push_back(const T &val) {
        if (full()) {
            resize();
        }
        // 在指定的内存空间中构造对象
        _allocator.construct(_last, val);
        _last++;
    }

    // 从容器尾部删除元素（需要将对象的析构和内存释放分开处理）
    void pop_back() {
        if (!empty()) {
            _last--;
            // 在指定的内存空间中析构对象
            _allocator.destroy(_last);
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
    int size() const {
        return _last - _first;
    }

private:
    T *_first;  // 指向数组起始的位置
    T *_last;   // 指向数组中有效元素的后继位置
    T *_end;    // 指向数组空间的后继位置
    Alloc _allocator;   // 定义容器空间配置器的对象

    // 扩容操作
    void resize() {
        int size = _end - _first;
        // 开辟数组的内存空间
        T *_ptemp = _allocator.allocate(size * 2);
        // 在指定的内存空间中构造对象
        for (int i = 0; i < size; i++) {
            _allocator.construct(_ptemp + i, _first[i]);
        }

        // 析构原来容器内的有效元素
        for (T *p = _first; p != _last; p++) {
            _allocator.destroy(p);
        }

        // 释放原来的数组内存
        _allocator.deallocate(_first);

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

    Person(const Person &p) {
        cout << "call Person(const Person &p)" << endl;
    }

    ~Person() {
        cout << "call ~Person()" << endl;
    }

};

void test01() {
    cout << "============= test01() =============" << endl;

    MyVector<int> v;
    for (int i = 0; i < 20; i++) {
        int val = rand() % 100;
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
    cout << "\n\n============= test02() =============" << endl;

    Person p1, p2, p3;
    cout << "------------------------------------------" << endl;
    MyVector<Person> v;
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    cout << "------------------------------------------" << endl;
    v.pop_back();
    cout << "------------------------------------------" << endl;
}

int main() {
    // 设置随机数种子
    srand(time(nullptr));

    test01();
    test02();
    return 0;
}
