/**
 * 模板的完全特例化和部分特例化
 */

#include <iostream>

using namespace std;

// 模板的实参推演

template<typename T>
void func(T a) {
    cout << "func => " << __PRETTY_FUNCTION__ << endl;
}

template<typename R, typename A1, typename A2>
void func2(R (*)(A1, A2)) {
    cout << "func2 => " << __PRETTY_FUNCTION__ << endl;
}

template<typename R, typename T, typename A1, typename A2>
void func3(R (T::*)(A1, A2)) {
    cout << "func3 => " << __PRETTY_FUNCTION__ << endl;
}

int sum(int a, int b) {
    return a + b;
}

class Test {

public:
    int sum(int a, int b) {
        return a + b;
    }

};

int main() {
    func(10);
    func("aaa");
    func(sum);
    func2(sum);
    func3(&Test::sum);
    return 0;
}