/**
 * 标准输入流
 */
#include <iostream>

using namespace std;

/**
 * cin.get() 读取输入的单个字符, 包括换行符
 *
 * <p> 比如输入 as, 缓冲区存放的是 a, s, 换行符
 */
void test01() {
    char c = cin.get();
    cout << "c = " << c << endl;    // 第一次读取到 a

    c = cin.get();
    cout << "c = " << c << endl;    // 第二次读取到 s

    c = cin.get();
    cout << "c = " << c << endl;    // 第三次读取到换行符

    c = cin.get();
    cout << "c = " << c << endl;    // 第四次等待下次输入
}

/**
 * cin.get(arg1, arg2) 读取输入的多个字符, 不包括换行符
 */
void test02() {
    char buffer[1024];
    cin.get(buffer, 1024);  // 不会读取换行符, 换行符仍然留在缓冲区
    cout << buffer << endl;

    char c = cin.get();
    if (c == '\n') {
        cout << "换行符还在缓冲区";
    } else {
        cout << "换行符不在缓冲区";
    }
}

/**
 * cin.getline(arg1, arg2) 读取输入的一行字符, 包括换行符
 */
void test03() {
    char buffer[1024];
    cin.getline(buffer, 1024);  // 会读取换行符并舍弃掉, 换行符不会留在缓冲区
    cout << buffer << endl;

    char c = cin.get();
    if (c == '\n') {
        cout << "换行符还在缓冲区";
    } else {
        cout << "换行符不在缓冲区";
    }
}

/**
 * cin.ignore(arg1) 忽略读取一个或多个字符
 *
 * <p> 比如, 输入 abcd, 最终只会输出 c = d
 */
void test04() {
    cin.ignore();       // 忽略读取一个字符
    cin.ignore(2);   // 忽略读取两个字符
    char c = cin.get();
    cout << "c = " << c << endl;
}

/**
 * cin.peek() 查看缓冲区是否有数据
 *
 * <p> 比如, 输入 ab, 第一次输出 c = a, 第二次也是输出 c = a
 */
void test05() {
    char c = cin.peek();    // 检测缓冲区是否有字符, 如果有则返回第一个字符, 且不会清理掉缓冲区中的任何字符
    cout << "c = " << c << endl;

    c = cin.get();
    cout << "c = " << c << endl;
}

/**
 * cin.putback(arg1) 将读取到的字符放回缓冲区
 *
 * <p> 比如, 输入 abcd, 最终输出的是 abcd
 */
void test06() {
    char c = cin.get();
    cin.putback(c);     // 将读取到的字符放回缓冲区

    char buffer[1024];
    cin.getline(buffer, 1024);
    cout << buffer << endl;
}

int main() {
    // test01();
    // test02();
    // test03();
    // test04();
     // test05();
    // test06();
    return 0;
}
