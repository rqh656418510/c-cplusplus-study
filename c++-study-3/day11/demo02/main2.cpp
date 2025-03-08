/**
 * function的实现原理
 */

#include <iostream>
#include <functional>
#include <string>

using namespace std;

// 定义类模板
// 这里的 Fty 代表任意函数签名，如 R(ARG1, ARG2)
template<typename Fty>
class myfunction {

};

/**
 * @brief 模板类的特化，支持特定的函数签名 R(ARG1, ARG2)
 * @tparam R 代表返回值类型
 * @tparam ARG1 代表第一个参数类型
 * @tparam ARG2 代表第二个参数类型
 */
template<typename R, typename ARG1, typename ARG2>
class myfunction<R(ARG1, ARG2)> {

public:
    // 定义函数指针类型，指向 R(ARG1, ARG2) 类型的函数
    using PFUNC = R(*)(ARG1, ARG2);

    /**
     * @brief 构造函数，接收一个函数指针，并存储起来
     * @param pfunc 指向函数的指针
    */
    myfunction(PFUNC pfunc) : _pfunc(pfunc) {

    }

    /**
     * @brief 重载小括号运算符，使对象可以像函数一样调用
     * @param arg1 传递给存储函数的第一个参数
     * @param arg2 传递给存储函数的第二个参数
     * @return 调用存储函数的返回值
    */
    R operator()(ARG1 arg1, ARG2 arg2) {
        return _pfunc(arg1, arg2);
    }

private:
    // 存储函数指针
    PFUNC _pfunc;

};

int sum(int a, int b) {
    return a + b;
}

int main() {
    // 创建 myfunction 对象，并绑定 sum 函数
    myfunction<int(int, int)> func1 = sum;

    // 通过 func1 调用 sum
    int result = func1(3, 5);
    cout << "result: " << result << endl;

    return 0;
}