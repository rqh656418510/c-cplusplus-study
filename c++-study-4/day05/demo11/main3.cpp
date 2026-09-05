/**
 * windows临界区、其他各种mutex互斥量
 *
 * （c) std::recursive_mutex 的使用
 */

#include <iostream>
#include <mutex>

class MyClass {
public:
    void process(int count) {
        // 获取锁
        std::unique_lock<std::recursive_mutex> lock(m_mutex);

        std::cout << "count = " << count << std::endl;

        if (count > 0) {
            // 递归调用，再次获取同一把锁
            process(count - 1);
        }

        // 这里不需要手动调用 unlock()，离开作用域后，unique_lock 析构时会自动释放锁
    }

private:
    std::recursive_mutex m_mutex;  // 递归互斥锁
};

int main() {
    MyClass obj;

    obj.process(3);

    return 0;
}