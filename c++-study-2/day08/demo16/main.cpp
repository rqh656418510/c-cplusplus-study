/**
 * 文件的读写操作
 */
#include <iostream>
#include <fstream>

using namespace std;

// 写文件
void test01() {
    ofstream ofs;
    ofs.open("/tmp/test.txt", ios::out | ios::trunc);
    if (!ofs.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }
    ofs << "Hello World 1" << endl;
    ofs << "Hello World 2" << endl;
    ofs << "Hello World 3" << endl;
    ofs.flush();
    ofs.close();
    cout << "文件写入完成" << endl;
}

// 第一种读取文件的方式（不推荐使用）：按行读取, 会忽略空白字符（如空格、换行符）
void test02() {
    ifstream ifs;
    ifs.open("/tmp/test.txt", ios::in);
    if (!ifs.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }

    // 按行读取
    char buffer[1024];
    while (ifs >> buffer) {
        cout << buffer << endl;
    }

    ifs.close();
}

// 第二种读取文件的方式（推荐使用）：按行读取
void test03() {
    ifstream ifs;
    ifs.open("/tmp/test.txt", ios::in);
    if (!ifs.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }

    // 按行读取, 会忽略空白字符（如空格、换行符）, 这样会导致整行内容无法被完整读取
    string line;
    while (getline(ifs, line)) {
        cout << line << endl;
    }

    ifs.close();
}

// 第三种读取文件的方式（不推荐使用）：按单个字符读取
void test04() {
    ifstream ifs;
    ifs.open("/tmp/test.txt", ios::in);
    if (!ifs.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }

    // 按单个字符读取
    char c;
    while ((c = ifs.get()) != EOF) {
        cout << c;
    }

    ifs.close();
}

int main() {
    cout << "------ test01() ------" << endl;
    test01();
    cout << "------ test02() ------" << endl;
    test02();
    cout << "------ test03() ------" << endl;
    test03();
    cout << "------ test04() ------" << endl;
    test04();
    return 0;
}
