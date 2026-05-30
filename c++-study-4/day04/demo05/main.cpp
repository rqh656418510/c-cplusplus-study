/**
 * shared_ptr使用场景、陷阱、性能分析、使用建议
 *
 * (a) shared_ptr 的使用场景
 */

#include <iostream>
#include <memory>

using namespace std;

// shared_ptr 作为函数返回值
shared_ptr<int> create(int value) {
    return make_shared<int>(value);
}

// shared_ptr 作为函数返回值
shared_ptr<int> func1(int value) {
    shared_ptr<int> sp = create(value);
    return sp;
}

int main() {
    shared_ptr<int> sp = func1(100);  // 这里的引用计数依然是 1，因为编译器通常会优化
    return 0;
}