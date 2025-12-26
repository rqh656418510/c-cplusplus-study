/**
 * 迭代器精彩演绎，失效分析及弥补、实战
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

// vector 的迭代器
void test0() {
    vector<string> v1 = {"a", "b", "c", "d", "e"};

    // 普通正向迭代器
    for (vector<string>::iterator it = v1.begin(); it != v1.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 只读正向迭代器
    for (vector<string>::const_iterator it = v1.cbegin(); it != v1.cend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 普通反向迭代器
    for (vector<string>::reverse_iterator it = v1.rbegin(); it != v1.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 只读反向迭代器
    for (vector<string>::const_reverse_iterator it = v1.crbegin(); it != v1.crend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

// vector 迭代器支持的操作
void test1() {
    vector<string> v1 = {"a", "b", "c", "d", "e"};
    vector<string>::iterator it = v1.begin();

    // 迭代器支持 * 操作
    cout << *it << endl;

    // 迭代器支持 [] 操作
    cout << it[1] << endl;

    // 迭代器支持 ++ 操作
    ++it;
    cout << *it << endl;

    // 迭代器支持 -- 操作
    --it;
    cout << *it << endl;
}

// vector 迭代器失效问题的解决
void test2() {
    vector<int> v1 = {1, 2, 3, 4, 5};

    // 一边遍历 vector，一边删除元素
    for (vector<int>::iterator it = v1.begin(); it != v1.end();) {
        if (*it % 2 == 0) {
            // 正确写法：使用 erase() 返回的新迭代器，erase() 返回指向被删除元素下一个位置的有效迭代器
            it = v1.erase(it);
        } else {
            ++it;
        }
    }

    for_each(v1.begin(), v1.end(), [](int item) { cout << item << " "; });

    cout << endl;
}

// vector 迭代器失效问题的解决
void test3() {
    vector<int> v1 = {1, 2, 3};

    // 一边遍历 vector，一边插入元素
    for (auto it = v1.begin(); it != v1.end();) {
        if (*it == 2) {
            it = v1.insert(it, 100);  // 正确写法：使用 insert() 返回的新迭代器
            it += 2;                     // 跳过原元素和新插入的元素
        } else {
            ++it;
        }
    }

    for_each(v1.begin(), v1.end(), [](int item) { cout << item << " "; });

    cout << endl;
}

struct conf {
    char name[40];
    char content[100];
};

char *getConfInfo(vector<conf *> &conflist, const char *name) {
    for (vector<conf *>::iterator it = conflist.begin(); it != conflist.end(); ++it) {
        if (strcmp((*it)->name, name) == 0) {
            return (*it)->content;
        }
    }
    return nullptr;
}

// vector 的常用操作与内存释放
void test4() {
    // 手动申请内存
    conf *pconf1 = new conf;
    snprintf(pconf1->name, sizeof(pconf1->name), "ServerName");
    snprintf(pconf1->content, sizeof(pconf1->content), "UserServer");

    // 手动申请内存
    conf *pconf2 = new conf;
    snprintf(pconf2->name, sizeof(pconf2->name), "ServerId");
    snprintf(pconf2->content, sizeof(pconf2->content), "0001");

    // 通过 vector 存储指针类型的数据
    vector<conf *> conflist;
    conflist.push_back(pconf1);
    conflist.push_back(pconf2);

    const char *name = "ServerId";
    char *confInfo = getConfInfo(conflist, name);
    if (confInfo != nullptr) {
        cout << name << " = " << confInfo << endl;
    } else {
        cout << "not found conf for " << name << endl;
    }

    // 必须手动释放内存，否则会造成内存泄漏
    for (vector<conf *>::iterator it = conflist.begin(); it != conflist.end(); ++it) {
        delete (*it);
    }

    // 清空容器（可选）
    conflist.clear();

};

int main() {
    test0();
    test1();
    test2();
    test3();
    test4();
    return 0;
}