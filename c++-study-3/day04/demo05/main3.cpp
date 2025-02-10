/**
 * vector容器的迭代器iterator实现
 *
 * <p> 解决容器的迭代器失效问题
 */
#include <iostream>
#include <cstring>

using namespace std;

// 类模板
template<typename T>
// 空间配置器（负责内存开辟、内存释放、对象构造、对象析构）
struct Allocator {

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
        new(p)T(val);
    }

    // 对象析构
    void destroy(T *p) {
        // ~T() 代表了 T 类型对象的析构函数
        p->~T();
    }

};

// 类模板
template<typename T, typename Alloc = Allocator<T>>
// 向量容器
class Vector {

public:
    // 构造函数
    Vector(int size = 10) {
        // 开辟数组的内存空间
        _first = _allocator.allocate(size);
        _last = _first;
        _end = _first + size;
    }

    // 析构函数（先析构容器内的有效元素，然后再释放 _first 指针指向的堆内存）
    ~Vector() {
        // 析构容器内的有效元素
        for (T *p = _first; p != _last; p++) {
            _allocator.destroy(p);
        }

        // 释放堆上的数组内存
        _allocator.deallocate(_first);
        _first = _last = _end = nullptr;
    }

    // 拷贝构造函数
    Vector(const Vector<T> &v) {
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
    Vector<T> &operator=(const Vector<T> &v) {
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
            verify(_last - 1, _last - 1);
            _last--;
            // 在指定的内存空间中析构对象
            _allocator.destroy(_last);
        }
    }

    // 返回容器尾部的元素
    T back() const {
        if (empty()) {
            throw "Vector is empty!";
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

    // 重载中括号运算符
    T &operator[](int index) {
        if (index < 0 || index >= size()) {
            throw "OutOfRangeException";
        }
        return _first[index];
    }

    // 迭代器
    class iterator {

    public:

        friend class Vector<T, Alloc>;

        iterator(Vector<T, Alloc> *pvec = nullptr, T *p = nullptr) : _pVec(pvec), _ptr(p) {
            // 维护迭代器的单向链表结构
            Iterator_Base *itb = new Iterator_Base(this, _pVec->_head._next);
            _pVec->_head._next = itb;
        }

        // 重载不等于运算符
        bool operator!=(const iterator &other) const {
            // 判断迭代器指向的容器是不是同一个
            if (_pVec == nullptr || _pVec != other._pVec) {
                throw "Iterator incompatable!";
            }
            return _ptr != other._ptr;
        }

        // 重载前置 ++ 运算符
        iterator &operator++() {
            // 检测迭代器的有效性
            if (_pVec == nullptr) {
                throw "Iterator invalid!";
            }
            _ptr++;
            return *this;
        }

        // 重载后置 ++ 运算符
        iterator operator++(int) {
            // 检测迭代器的有效性
            if (_pVec == nullptr) {
                throw "Iterator invalid!";
            }
            return iterator(_ptr++);
        }

        // 解引用运算符重载
        T &operator*() const {
            // 检测迭代器的有效性
            if (_pVec == nullptr) {
                throw "Iterator invalid!";
            }
            return *_ptr;
        }

    private:
        T *_ptr;
        Vector<T, Alloc> *_pVec; // 当前迭代器是哪个容器的对象
    };

    // 返回的是容器底层首元素的迭代器的表示
    iterator begin() {
        return iterator(this, _first);
    }

    // 返回的是容器末尾元素后继位置的迭代器的表示
    iterator end() {
        return iterator(this, _last);
    }

    // 通过迭代器往容器插入元素
    // 这里暂时不考虑容器扩容，也不考虑 it._prt 的指针合法性
    iterator insert(iterator it, const T &val) {
        verify(it._ptr - 1, _last);

        // 重新分配数组的内存空间，并往右边移动数组元素
        T *p = _last;
        while (p > it._ptr) {
            _allocator.construct(p, *(p - 1));
            _allocator.destroy(p - 1);
            p--;
        }
        _allocator.construct(p, val);

        _last++;
        return iterator(this, p);
    }

    // 通过迭代器往容器删除元素
    iterator erase(iterator it) {
        verify(it._ptr - 1, _last);

        // 重新分配数组的内存空间，并往左边移动数组元素
        T *p = it._ptr;
        while (p < _last - 1) {
            _allocator.destroy(p);
            _allocator.construct(p, *(p + 1));
            p++;
        }
        _allocator.destroy(p);

        _last--;
        return iterator(this, it._ptr);
    }

private:
    T *_first;  // 指向数组起始的位置
    T *_last;   // 指向数组中有效元素的后继位置
    T *_end;    // 指向数组空间的后继位置
    Alloc _allocator;   // 定义容器空间配置器的对象

    // 迭代器的单向链表结构
    struct Iterator_Base {
        Iterator_Base(iterator *cur = nullptr, Iterator_Base *next = nullptr) : _cur(cur), _next(next) {

        }

        iterator *_cur;
        Iterator_Base *_next;
    };

    Iterator_Base _head;

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

    // 维护迭代器的单向链表
    void verify(T *start, T *end) {
        Iterator_Base *cur = &this->_head;
        Iterator_Base *next = this->_head._next;
        while (next != nullptr) {
            if (next->_cur->_ptr >= start && next->_cur->_ptr <= end) {
                // 迭代器失效，将迭代器持有的容器指针置为空
                next->_cur->_pVec = nullptr;
                // 在迭代器链表中，删除当前迭代器节点，并继续判断后面的迭代器节点是否失效
                cur->_next = next->_next;
                delete next;
                next = cur->_next;
            } else {
                next = next->_next;
            }
        }
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
    cout << "============ test01() ============" << endl;

    // 往容器插入元素
    Vector<int> v(100);
    for (int i = 0; i < 20; i++) {
        int val = rand() % 100;
        v.push_back(val);
        cout << val << " ";
    }
    cout << endl;

    // 将容器中的所有偶数删除掉
    for (Vector<int>::iterator it = v.begin(); it != v.end();) {
        if (*it % 2 == 0) {
            // 更新迭代器
            it = v.erase(it);
        } else {
            ++it;
        }
    }

    // 使用 For 循环遍历容器，会自动调用容器类的 begin() 和 end() 函数
    for (int item : v) {
        cout << item << " ";
    }
    cout << endl;
}

void test02() {
    cout << "============ test02() ============" << endl;

    // 往容器插入元素
    Vector<int> v(100);
    for (int i = 0; i < 20; i++) {
        int val = rand() % 100;
        v.push_back(val);
        cout << val << " ";
    }
    cout << endl;

    // 给容器中所有的偶数前面添加一个小于该偶数的数字
    for (Vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if (*it % 2 == 0) {
            // 更新迭代器
            it = v.insert(it, *it - 1);
            ++it;
        }
    }

    // 使用 For 循环遍历容器，会自动调用容器类的 begin() 和 end() 函数
    for (int item : v) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    // 设置随机数种子
    srand(time(nullptr));

    test01();
    test02();

    return 0;
}
