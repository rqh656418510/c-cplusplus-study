/**
 * 可调用对象、std::function、std::bind
 *
 * (d) std::function 综合使用案例
 */

#include <functional>
#include <iostream>

class CB {
public:
    explicit CB(const std::function<void()>& f) : fcallback(f) {
    }

    void runCallBack() {
        fcallback();
    }

private:
    std::function<void()> fcallback;
};

// 函数对象
class CT {
public:
    void operator()(void) {
        std::cout << "void CT::operator()(void)" << std::endl;
    }
};

int main() {
    CT ct;
    CB cb(ct);
    cb.runCallBack();
    return 0;
}