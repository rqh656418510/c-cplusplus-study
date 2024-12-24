/**
 * 理解类模板
 */

#include <iostream>

using namespace std;

// 类模板
template<typename T>
// 顺序栈
class SeqStack {

public:

    // 建议构造和析构函数的名称不加 <T>，而且其他使用模板的地方都加上类型参数类列表，比如 <T>

    // 构造函数
    SeqStack(int size = 10) : _pstatck(new T[size]), _top(-1), _size(size) {

    }

    // 析构函数
    ~SeqStack() {
        if (_pstatck != nullptr) {
            delete[]_pstatck;
            _pstatck = nullptr;
        }
    };

    // 拷贝构造函数
    SeqStack(const SeqStack<T> &stack) : _top(stack._top), _size(stack._size) {
        // 实现深拷贝
        _pstatck = new T[_size];
        for (int i = 0; i < _top; i++) {
            _pstatck[i] = stack._pstatck[i];
        }
    }

    SeqStack<T> &operator=(const SeqStack<T> &stack) {
        if (this == stack) {
            return *this;
        }

        if (_pstatck != nullptr) {
            delete[]_pstatck;
        }

        // 实现深拷贝
        _top = stack._top;
        _size = stack._size;
        _pstatck = new T[_size];
        for (int i = 0; i < _top; i++) {
            _pstatck[i] = stack._pstatck[i];
        }

        return *this;
    }

    // 入栈
    void push(const T &val) {
        if (full()) {
            resize();
        }
        _pstatck[++_top] = val;
    }

    // 弹栈
    void pop() {
        if (!empty()) {
            --_top;
        }
    }

    // 获取栈顶元素
    T top() const {
        if (empty()) {
            throw "stack is empty!";
        }
        return _pstatck[_top];
    }

    // 栈是否满了
    bool full() const {
        return _top == _size - 1;
    }

    // 栈是否为空
    bool empty() const {
        return _top == -1;
    }

private :
    T *_pstatck; // 动态开辟数组，存储顺序栈的元素
    int _top;    // 指向栈顶元素的位置
    int _size;   // 数组的总大小

    // 扩容操作
    void resize() {
        T *ptmp = new T[_size * 2];
        for (int i = 0; i < _top; i++) {
            ptmp[i] = _pstatck[i];
        }
        delete[]_pstatck;
        _pstatck = ptmp;
        _size *= 2;
    }

};

int main() {
    // 设置随机数种子
    srand(time(nullptr));

    // 类模板的选择性实例化
    // 实例化后的模板类 class SeqStack<int> { };
    SeqStack<int> stack;
    for (int i = 0; i < 20; i++) {
        stack.push(rand() % 100);
    }

    while (!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
    return 0;
}
