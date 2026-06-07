/**
 * 返回unique_ptr、删除器、尺寸、智能指针
 */

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

unique_ptr<int> func() {
    unique_ptr<int> up(new int(100));
    return up;  // 返回一个局部对象，编译器会生成一个临时对象，并调用 unique_ptr 的移动构造函数
}

// 返回 unique_ptr 类型
void test01() {
    unique_ptr<int> up = func();  // 接收函数返回的 unique_ptr，调用 unique_ptr 的拷贝构造函数

    unique_ptr<int> up2;  // 接收函数返回的 unique_ptr
    up2 = func();         // 调用 unique_ptr 的赋值运算符
}

void myDeleter(int *p) {
    delete p;
    p = nullptr;
    cout << "delete int *" << endl;
}

// 自定义删除器（使用普通函数）
void test02() {
    // 使用 typedef 定义一个函数指针类型，类型名称是 func
    typedef void (*func)(int *);
    unique_ptr<int, func> up(new int(100), myDeleter);

    // 使用 using 定义一个函数指针类型，类型名称是 func2
    using func2 = void (*)(int *);
    unique_ptr<int, func2> up2(new int(100), myDeleter);

    // 或者直接省去函数指针类型的定义
    unique_ptr<int, void (*)(int *)> up3(new int(100), myDeleter);

    // 或者配合使用 typedef 和 decltype
    typedef decltype(myDeleter) *func3;
    unique_ptr<int, func3> up5(new int(100), myDeleter);

    // 或者配合使用 using 和 decltype
    using func4 = decltype(myDeleter) *;
    unique_ptr<int, func4> up6(new int(100), myDeleter);

    // 或者直接使用 decltype 获取具体的类型
    unique_ptr<int, decltype(myDeleter) *> up4(new int(100), myDeleter);
}

// 定义 Lambda 表达式
auto myDelLambda = [](int *p) {
    delete p;
    p = nullptr;
    cout << "delete int *" << endl;
};

// 自定义删除器（使用 Lambda 表达式）
void test03() {
    // 配合使用 decltype 和 Lambda 表达式
    unique_ptr<int, decltype(myDelLambda)> up(new int(100), myDelLambda);

    // 直接使用 Lambda 表达式
    unique_ptr<int, void (*)(int *)> up2(new int(100), [](int *p) {
        delete p;
        p = nullptr;
        cout << "delete int *" << endl;
    });
}

// 不是同一种类型的说明
void test04() {
    auto lambda1 = [](int *p) {
        delete p;
        cout << "delete by lambda1" << endl;
    };

    auto lambda2 = [](int *p) {
        delete p;
        cout << "delete by lambda2" << endl;
    };

    unique_ptr<int, decltype(lambda1)> up1(new int(100), lambda1);

    unique_ptr<int, decltype(lambda2)> up2(new int(200), lambda2);

    // 类型不相同，不可以放入到元素类型为该对象类型的容器里面
    vector<unique_ptr<int, decltype(lambda1)>> vec;
    vec.emplace_back(move(up1));
    // vec.emplace_back(move(up2));  // up1 与 up2 的删除器类型不相同，两者不属于同一种类型，不可以放入同一个容器中
}

// unique_ptr 的大小
void test05() {
    int *p;
    unique_ptr<int> up;
    int length1 = sizeof(p);   // 8 个字节（64 位系统）
    int length2 = sizeof(up);  // 8 个字节（64 位系统）
    cout << length1 << endl;
    cout << length2 << endl;

    unique_ptr<int, void (*)(int *)> up3(new int(100), myDeleter);
    int length3 = sizeof(up3);
    cout << length3 << endl;  // 16 个字节（64 位系统）
}

int main() {
    // test01();
    // test02();
    // test03();
    // test04();
    test05();
    return 0;
}