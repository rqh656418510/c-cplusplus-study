/**
 * 掌握构造函数和析构函数
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

private:
    int *_pstatck; // 动态开辟数组，存储顺序栈的元素
    int _top;   // 指向栈顶元素的位置
    int _size;  // 数组扩容的总大小

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

void test01() {
    cout << "===== call test01() =====" << endl;
    SeqStack s(5);
    for (int i = 0; i < 15; i++) {
        s.push(rand() % 100);
    }

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

void test02() {
    cout << "===== call test02() =====" << endl;
    SeqStack *s = new SeqStack(5);
    for (int i = 0; i < 15; i++) {
        s->push(rand() % 100);
    }

    while (!s->empty()) {
        cout << s->top() << " ";
        s->pop();
    }
    cout << endl;

    delete s;
}

int main() {
    // 设置随机数种子
    srand(time(nullptr));

    test01();
    test02();
    return 0;
}
