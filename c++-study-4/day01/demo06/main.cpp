/**
 * string类型介绍
 */

#include <string.h>

#include <iostream>
#include <string>

using namespace std;

// C 语言中字符串的初始化
void test01() {
    // 使用字符串字面量初始化：末尾自动追加 '\0'，其余元素补 0
    char str1[100] = "C++";

    // 等价于上面 s1 的写法效果，显式写出 '\0'，其余元素补 0
    char str2[100] = {'C', '+', '+', '\0'};

    // 不指定字符串长度，让编译器自动推导，实际大小是 4（包括末尾的 '\0'）
    char str3[] = "C++";

    // 使用字符列表初始化（末尾必须要有 '\0'，否则不是字符串）
    char str4[] = {'C', '+', '+', '\0'};

    // 部分初始化：其余元素补 0（非字符串语义，但结果满足 '\0' 结尾）
    char str5[100] = {'C', '+', '+'};
}

// C++ 中字符串的初始化
void test02() {
    // 默认初始化，s1 是空字符串，表示里面没有字符
    string s1;

    // 将指定的字符串内容拷贝到 s2 所代表的一段内存中，拷贝时不包括字符串末尾的 '\0'
    string s2 = "I Love C++";

    // 跟上面字符串 s2 的写法效果一样
    string s3("I Love C++");

    // 列表初始化
    string s4{"I Love C++"};

    // 将字符串 s2 的内容拷贝到 s4 所代表的一段内存中
    string s5 = s2;

    // 将 s5 初始化为连续 5 个字符 'a' 组成的字符串（aaaaa），可能会在系统内部创建临时对象
    string s6(5, 'a');

    // 从 s2 的下标 2（第 3 个字符）开始，连续拷贝到字符串末尾，构造新的字符串
    string s7(s2, 2);

    // 从 s2 的下标 2（第 3 个字符）开始，连续拷贝 4 个字符，构造新的字符串
    string s8(s2, 2, 4);

    // 通过字符数组（必须有一个元素是 '\0'，否则会出现未定义行为）初始化字符串
    char buf[] = {'a', 'b', 'c', '\0'};
    string s9(buf);
}

// C++ 中字符串的 API
void test03() {
    string s1 = "abcde";

    // 字符串长度
    cout << "size: " << s1.size() << endl;
    cout << "length: " << s1.length() << endl;
    cout << "empty: " << s1.empty() << endl;

    // 字符串下标操作
    if (s1.length() > 3) {
        s1[4] = 'f';
        cout << s1 << endl;
    }

    // 字符串拼接
    string s2 = "123";
    string s3 = "456";
    string s4 = s2 + s3;
    cout << s4 << endl;

    // 字符串赋值
    string s5 = "abc";
    string s6 = "123";
    s6 = s5;

    // 字符串比较
    string s7 = "A";
    string s8 = "a";
    cout << "compare: " << s7.compare(s8) << endl;

    // 获取字符串指针
    string s9 = "hello pointer";
    const char* ptr1 = s9.c_str();
    char buf[100] = {0};
    if (sizeof(buf) > (s9.size() + 1)) {
        strcpy(buf, ptr1);
        cout << buf << endl;
    }

    // 字符串与范围 for 的使用
    string s10 = "hello c++";
    // 通过范围 for 遍历字符串所有元素，使用常量引用
    for (const char& c : s10) {
        cout << c;
    }
    cout << endl;
    // 通过范围 for 和引用遍历字符串所有元素，并更改其元素的值，使用普通引用
    for (char& c : s10) {
        c = toupper(c);
        cout << c;
    }
    cout << endl;
}

int main() {
    test01();
    test02();
    test03();
}