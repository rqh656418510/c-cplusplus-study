/**
 * unique_lock详解
 *
 * (b) unique_lock 的所有权传递
 */

#include <iostream>
#include <mutex>

void test01() {
    std::mutex mx;
    std::unique_lock<std::mutex> lock1(mx);

    // 非法代码，所有权是不允许复制的
    // std::unique_lock<std::mutex> lock2(lock1);
    // std::unique_lock<std::mutex> lock2 = lock1;

    // 合法代码，所有权是允许转移的
    // 所有权转移后，lock1 的互斥量指向为空（不持有任何锁），而 lock2 的互斥量指向为 mx
    std::unique_lock<std::mutex> lock2(std::move(lock1));
}

std::unique_lock<std::mutex> getLock(std::mutex &mx) {
    std::unique_lock<std::mutex> lock(mx);
    // 函数结果返回 unique_lock 局部对象是可以的，系统会生成临时的 unique_lock 对象，并调用 unique_lock 的移动构造函数
    return lock;
}

void test02() {
    std::mutex mx;
    std::unique_lock<std::mutex> lock = getLock(mx);
}

int main() {
    test01();
    test02();
    return 0;
}