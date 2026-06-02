/**
 * shared_ptr使用场景、陷阱、性能分析、使用建议
 *
 * (b) shared_ptr 的使用陷阱
 */

#include <iostream>
#include <memory>

using namespace std;

void proc(shared_ptr<int> sp) {
    return;
}

// 裸指针与智能指针混合使用
void test01() {
    int *p = new int(100);     // 裸指针
    proc(shared_ptr<int>(p));  // 使用 shared_ptr 临时对象作为函数参数
    *p = 45;                   // 错误写法（存在未定义行为），因为 proc() 执行结束后，p 指向的内存已经被 shared_ptr 临时对象释放掉
}

// 使用裸指针初始化多个智能指针
void test02() {
    int *p = new int(100);
    shared_ptr<int> sp1(p);
    shared_ptr<int> sp2(p);  // 错误写法，使用同一个裸指针初始化多个 shared_ptr
    // 离开作用域后，p 指向的内存会被 delete 两次（因为 sp1 与 sp2 的引用计数是互相独立的，没有任何关联关系），导致程序运行崩溃
}

// 谨慎使用 get() 返回的裸指针
void test03() {
    shared_ptr<int> sp = make_shared<int>(100);
    int *p = sp.get();
    // delete p;  // 错误写法，不能将 get() 返回的裸指针 delete 掉，否则会重复释放内存，导致程序运行崩溃
    // shared_ptr<int> sp2(p); // 错误写法，不能将 get() 返回的裸指针绑定到其他 shared_ptr，否则会重复释放内存，导致程序运行崩溃
}

class MyClass {
public:
    shared_ptr<MyClass> getSelf() {
        return shared_ptr<MyClass>(this);  // 错误写法（危险操作）
    }
};

// 不要将 this 作为 shared_ptr 返回
void test04() {
    shared_ptr<MyClass> p1 = make_shared<MyClass>();
    // shared_ptr<MyClass> p2 = p1->getSelf();  // p1 和 p2 独立管理同一对象（不共享引用计数），会导致重复释放内存
}

class CB;

class CA {
public:
    shared_ptr<CB> m_cb;
    ~CA() {
        cout << "~CA()" << endl;
    }
};

class CB {
public:
    shared_ptr<CA> m_ca;
    ~CB() {
        cout << "~CB()" << endl;
    }
};

// 应避免 shared_ptr 发生循环引用
void test05() {
    shared_ptr<CA> sp_ca = make_shared<CA>();
    shared_ptr<CB> sp_cb = make_shared<CB>();
    sp_ca->m_cb = sp_cb;
    sp_cb->m_ca = sp_ca;
    // 离开作用域后，由于存在循环引用，CA 和 CB 的对象都不会自动析构（释放内存）
}

int main() {
    // test01();
    // test02();
    // test03();
    // test04();
    // test05();
    return 0;
}