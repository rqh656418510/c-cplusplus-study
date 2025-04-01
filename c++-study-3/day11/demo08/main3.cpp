/**
 * 模板的完全特例化和部分特例化
 */

#include <iostream>

#if defined(__linux__)
    #define FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif defined(_WIN32)
    #define FUNCTION_SIGNATURE __FUNCSIG__
#endif

using namespace std;

// 模板的实参推演

template<typename T>
void func(T a) {
    cout << "func => " << FUNCTION_SIGNATURE << endl;
}

template<typename R, typename A1, typename A2>
void func2(R (*)(A1, A2)) {
    cout << "func2 => " << FUNCTION_SIGNATURE << endl;
}

template<typename R, typename T, typename A1, typename A2>
void func3(R (T::*)(A1, A2)) {
    cout << "func3 => " << FUNCTION_SIGNATURE << endl;
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