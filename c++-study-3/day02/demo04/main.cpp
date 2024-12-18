/**
 * 掌握对象的深拷贝和浅拷贝
 */

#include <iostream>

using namespace std;

// 顺序栈
class SeqStack {

public:
    // 构造函数
    SeqStack(int size = 10) {
        cout << "call SeqStack()" << endl;
        // 分配内存
        _pstatck = new int[size];
        _top = -1;
        _size = size;
    }

    // 析构函数
    ~SeqStack() {
        cout << "call ~SeqStack()" << endl;
        // 释放内存
        if (_pstatck != nullptr) {
            delete[] _pstatck;
            _pstatck = nullptr;
        }
    }

    // 拷贝构造函数
    SeqStack(const SeqStack &stack) {
        cout << "call SeqStack(const SeqStack &stack)" << endl;
        // 深拷贝（重新分配内存）
        _pstatck = new int[stack._size];
        for (int i = 0; i < stack._size; i++) {
            _pstatck[i] = stack._pstatck[i];
        }
        _top = stack._top;
        _size = stack._size;
    }

    // 运算符重载
    void operator=(const SeqStack &stack) {
        cout << "call operator=(const SeqStack &stack)" << endl;
        // 防止自赋值
        if (this == &stack) {
            return;
        }

        // 释放原来占用的内存空间
        if (_pstatck != nullptr) {
            delete[]_pstatck;
        }

        // 深拷贝（重新分配内存）
        _pstatck = new int[stack._size];
        for (int i = 0; i < stack._size; i++) {
            _pstatck[i] = stack._pstatck[i];
        }
        _top = stack._top;
        _size = stack._size;
    }

    // 入栈
    void push(int val) {
        if (full()) {
            resize();
        }
        _pstatck[++_top] = val;
    }

    // 弹栈
    void pop() {
        if (empty()) {
            return;
        }
        --_top;
    }

    // 获取栈顶元素
    int top() {
        return _pstatck[_top];
    }

    // 栈是否满了
    bool full() {
        return _top == _size - 1;
    }

    // 栈是否为空
    bool empty() {
        return _top == -1;
    }

    // 打印所有元素
    void print() {
        for (int i = 0; i < _size; i++) {
            cout << _pstatck[i] << " ";
        }
        cout << endl;
    }

    // 获取元素数量
    int size() {
        return _size;
    }

private:
    int *_pstatck; // 动态开辟数组，存储顺序栈的元素
    int _top;   // 指向栈顶元素的位置
    int _size;  // 数组的总大小

    // 扩容操作
    void resize() {
        // 分配新的内存空间
        int *pnew = new int[_size * 2];
        for (int i = 0; i < _size; i++) {
            pnew[i] = _pstatck[i];
        }
        // 释放旧的内存空间
        delete[] _pstatck;
        // 指向新的内存空间
        _pstatck = pnew;
        _size *= 2;
    }
};

int main() {
    // 设置随机数种子
    srand(time(nullptr));

    SeqStack s1(10);
    for (int i = 0; i < s1.size(); i++) {
        s1.push(rand() % 100);
    }
    s1.print();

    SeqStack s2 = s1;   // 默认会调用拷贝构造函数
    s2.print();

    SeqStack s3(s1);   // 默认会调用拷贝构造函数
    s3.print();

    s2 = s3;  // 赋值运算，不会调用拷贝构造函数，默认是浅拷贝，会发生内存泄漏（内存没有被正确释放），解决办法是通过运算符重载来实现深拷贝
    return 0;
}
