/**
 * 模板的完全特例化和部分特例化
 */

#include <iostream>
#include <cstring>

using namespace std;

// 模板
template<typename T>
bool compare(T a, T b) {
    cout << "template compare" << endl;
    return a > b;
}

// 模板特例化（实现字符串比较）
template<>
bool compare<const char *>(const char *s1, const char *s2) {
    cout << "string template compare" << endl;
    return strcmp(s1, s2) > 0;
}

int main() {
    compare(10, 20);

    // 如果不使用模板特例化，这里默认只会简单比较字符串指针的地址，并不符合预期行为
    compare("aaa", "bbb");

    return 0;
}
