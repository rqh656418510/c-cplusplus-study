/**
 * shared_ptr 的交叉引用（循环引用）问题
 */

#include <iostream>
#include <memory>

using namespace std;

// shared_ptr 智能指针的使用

class Resource {

public:
    Resource() {
        cout << "Resource()" << endl;
    }

    ~Resource() {
        cout << "~Resource()" << endl;
    }

    void show() {
        cout << "Using resource" << endl;
    }

};

int main() {
    // 创建一个 shared_ptr sp1，并管理 Resource 对象
    shared_ptr<Resource> sp1 = make_shared<Resource>();

    // 不建议这样写
    // shared_ptr<Resource> sp1(new Resource());

    // 打印引用计数
    cout << "Reference count: " << sp1.use_count() << endl;

    {
        // 创建一个 shared_ptr sp2，共享 sp1 的资源
        shared_ptr<Resource> sp2 = sp1;
        // 打印引用计数
        cout << "Reference count: " << sp1.use_count() << endl;
        // 访问资源
        sp2->show();
    } // 作用域结束后，sp2 自动析构，引用计数减少

    // 打印引用计数
    cout << "Reference count: " << sp1.use_count() << endl;

    return 0;
}