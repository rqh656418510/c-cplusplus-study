/**
 * 标准输出流
 */
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

/**
 * cout.put() 向缓冲区写入字符
 */
void test01() {
    cout.put('a');
}

/**
 * cout.write() 从缓冲区中写 N 个字符到当前输出流中
 */
void test02() {
    char buf[1024] = "hello world";
    cout.write(buf, strlen(buf));
}

/**
 * 通过流对象的成员函数实现格式化输出
 */
void test03() {
    int number = 99;
    cout.width(20);
    cout.fill('*');
    cout.setf(ios::left);       // 设置对齐的格式，比如左对齐
    cout.unsetf(ios::dec);      // 卸载十进制格式
    cout.setf(ios::hex);        // 设置十六进制格式
    cout.setf(ios::showbase);   // 强制输出整数的基数（八进制以 0 开头，十六禁止以 0x 开头）
    cout.unsetf(ios::hex);      // 卸载十六进制格式
    cout.setf(ios::oct);        // 设置八进制格式
    cout << number;
}

/**
 * 使用控制符的方式显示
 */
void test04() {
    int number = 30;
    cout << setw(20)
         << setfill('*')
         << setiosflags(ios::showbase)      // 强制输出整数的基数（八进制以 0 开头，十六禁止以 0x 开头）
         << setiosflags(ios::left)          // 设置对齐的格式，比如左对齐
         << hex     // 使用十六进制格式
         << number;
}

int main() {
    cout << endl << "------- test01() -------" << endl;
    test01();
    cout << endl << "------- test02() -------" << endl;
    test02();
    cout << endl << "------- test03() -------" << endl;
    test03();
    cout << endl << "------- test04() -------" << endl;
    test04();
    return 0;
}
