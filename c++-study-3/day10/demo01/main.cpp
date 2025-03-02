/**
 * 智能指针基础知识
 */

#include <iostream>

using namespace std;

// 模拟实现不带引用计数的智能指针
template<typename T>
class CSmartPtr {

public:
    CSmartPtr(T *ptr) : _ptr(ptr) {
        cout << "CSmartPtr()" << endl;
    }

    ~CSmartPtr() {
        cout << "~CSmartPtr()" << endl;
        delete _ptr;
        _ptr = nullptr;
    }

    CSmartPtr(const CSmartPtr<T>& src) {
        cout << "CSmartPtr(const CSmartPtr& src)" << endl;
        // 深拷贝
        this->_ptr = new T(*src._ptr);
    }

    // * 运算符重载函数
    T &operator*() {
        return *_ptr;
    }

    // -> 运算符重载函数
    T *operator->() {
        return _ptr;
    }

private:
    T *_ptr;
};

class Person {

public:
    Person(int age) : _age(age) {

    }

    void print() {
        cout << "age: " << _age << endl;
    }

private:
	int _age;
};

int main() {
    // 智能指针是利用栈上的对象出作用域后自动析构的特性，来实现资源的自动释放
    CSmartPtr<int> cptr(new int);
    *cptr = 30;

    // 错误用法，这样写必须手动执行 delete cptr 来释放资源，即失去智能指针自动释放资源的特性
    // CSmartPtr<int>* cptr = new CSmartPtr<int>(new int);

    CSmartPtr<Person> cptr2(new Person(30));
    cptr2->print();

    CSmartPtr<Person> cptr3(cptr2);
}